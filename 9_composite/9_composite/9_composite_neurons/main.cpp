#include <iostream>
#include <vector>
#include "headers.hpp"

using namespace std;
struct Neuron;

template <typename Self>
struct SomeNeurons
{
    template <typename T> void connect_to(T& other)
    {
      for (Neuron& from: *static_cast<Self*>(this))
      {
        for (Neuron& to: other)
        {
          from.out.push_back(&other);
          to.in.push_back(this);
        }
      }
    }
};

struct Neuron : SomeNeurons<Neuron>
{
  vector<Neuron*> in, out;
  unsigned int id;
  
  Neuron() {
    static int id {1};
    this->id = id++;
  }
  
  Neuron* begin() {return this;}
  Neuron* end() {return this + 1;}
  
  friend ostream &operator << (ostream &os, const Neuron &obj){
    for (Neuron* n: obj.out){
      os << n->id << "\t-->\t[" << obj.id << "]" << endl;
    }
    for (Neuron* n: obj.out){
      os << "[" << obj.id << "]\t-->\t" << n->id << endl;
    }
    return os;
  }
};

struct NeuronLayer : vector<Neuron>, SomeNeurons<NeuronLayer>
{
  NeuronLayer (int count)
  {
    while (count --> 0){
      emplace_back(Neuron{});
    }
  }
  
  friend ostream &operator<<(ostream &os, const NeuronLayer& obj){
    for (auto& n : obj ) os << n;
    return os;
  }
};

int main() {
  Neuron n1, n2;
  n1.connect_to(n2);
  cout << n1 << n2 << endl;
  
  NeuronLayer layer1 {2}, layer2{4};
}