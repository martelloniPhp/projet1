/*
* @@tagdynamic@@
* @@tagdepends:@@endtagdepends
*/
#include <vle/value/Value.hpp>
#include <vle/devs/DynamicsComp.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <vle/utils/State.hpp>
//#include <./state.cpp>
#include <cmath>
#include "state.cpp"



namespace vd = vle::devs;
namespace vv = vle::value;

namespace feu {
	
	
class NewCpp : public vd::DynamicsComp
{
	
	
 public:



std::vector<vle::utils::State*> listState;
std::vector<vle::utils::State*> listStateNew;
/*
std::vector<Etat*> listState;
std::vector<Etat*> listStateNew;
* */
float t_ignition;
float t_ambiente;
float m_extinction;
float m_depart;
float k1,k2,k3,k4,k5,k6;

 
  NewCpp(const vd::DynamicsCompInit& init,
                const vd::InitEventList& events)
        : vd::DynamicsComp(init, events)
  {
//std::cout<<"creation dyn multi"<< std::endl; 
	
	t_ignition = 573.15;
	t_ambiente = 298.15;
	m_depart = 100;
	m_extinction = 5.25;
	k1=0.03333; k2=0.5; k3=0.00445; k4=0.1; k5=0.0001; k6=0.01;
	listState.clear();
	state2 = new Etat();
	state2new = new Etat();
	int i=influanceur.size()/100;
	int j=influanceur.size()%100;

	std::string str = "0";  //non brule
	if((i==49)&&(j==49))
	{
		str="1"; //chauffe
		//state2new->setActivity(true);
		//state2->setActivity(true);
	}
	state2->setState(i,j,"0",t_ambiente,m_depart); //non brule
	state2new->setState(i,j,str,t_ambiente,m_depart);
	
	std::string key = "";
	key = std::to_string(i)+ "," +std::to_string(j);
    //influancess.emplace(key,state2);
    influanceur[key] = state2;
    influance.emplace_back(state2);
   // std::cout << "voisinage 2 " << ((Etat*)state2)->voisinage2.size() <<  std::endl;
  }
  virtual ~NewCpp()
  {
	
  }
  virtual vd::Time init(vle::devs::Time /*time*/) override
  {
//std::cout<<"init variables: "<< influanceur.size() << " " << listState.size()<<  std::endl;
	//init voisinage
	//std::cout <<  influancess["99,99"]->getPosition().i << std::endl;
	/*for(int i=0; i<influanceur.size();i++)
	{
		for(auto v : state2->voisinage)
		{
			//std::cout<< "[ "<< v.first<< "," << v.second<< "]"<< std::endl;
			if ((influanceur[i]->getPosition().i == state2->getPosition().i+v.first)&&(influanceur[i]->getPosition().j == state2->getPosition().j+v.second))
				{
					listState.emplace_back(influanceur[i]);
					//listStateNew.emplace_back(influance[i]);
				}
		}
				
	}*/
	std::string key = "";
	//std::cout<< state2->voisinage.size() << std::endl; 
	for(auto v : ((Etat*)state2)->voisinage2)
		{
		//	std::cout << v.first <<"," << v.second << std::endl;
		key = std::to_string(v.first+state2->getPosition().i)+ "," +std::to_string(v.second+state2->getPosition().j);
		if (influanceur.count(key) > 0)
			{
				listState.emplace_back(influanceur[key]);
				
			}
					//listStateNew.emplace_back(influancess[key]);
				
		}
	
	
	//std::cout<<"init variables: "<< influancess.size() << " " << listState.size() <<   std::endl;
	//state2->setState(0,1,"s1");
	//std::cout << "element [" << state2->getPosition().i << ", "<< state2->getPosition().j << "] voisin: " << listState.size() << "  " << influancess.size() << std::endl;
	/*for(auto s : listState){
		std::cout << "	[" << s->getPosition().i << ", "<< s->getPosition().j << "] " << std::endl;
	}*/
	/*if ((state2->getPosition().i == 49)&&(state2->getPosition().j == 49))
				{
	for(auto s : listStateNew)
			{
				s->setActivity(true);
				//std::cout << s->getPosition().i << "," <<s->getPosition().j << " activé" << std::endl;
				std::cout<<listStateNew.size()<<std::endl;
			}
	}*/
    return 0;
  }
  virtual void output(vle::devs::Time time,
                      vd::ExternalEventList& /*output*/) override 
  {
//std::cout<<"output multi [" << state2->getPosition().i << ", "<< state2->getPosition().j << "] " << state2->getVal() << " " << influanceur.size() << " nb voisins " << listState.size()  <<" time: "<< time << std::endl; 

 

 /*std::ofstream fichier("/home/martelloni/model/feuResultat/testFeu.txt", std::ios::out | std::ios::app);  // ouverture en écriture avec effacement du fichier ouvert

 

        if(fichier)

        {

               

                fichier << "output multi [" << state2->getPosition().i << ", "<< state2->getPosition().j << "] " << state2->getVal() << " " << influanceur.size() << " nb voisins " << listState.size()  <<" time: "<< time << std::endl; 

               
 

                fichier.close();

        }

        else

                std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;*/
  }
  virtual vd::Time timeAdvance() const override
  {
    //return vd::infinity;
   
	 if(state2new->getVal() ==   "4")//Burnt
			return vd::infinity;
		else
			return 1;
		
	
    //return 1;
  }
  virtual void internalTransition(vle::devs::Time time) override
  {
	   
float t=0;
float m=0;
int elapsed =0;
int e =0;
//std::cout << listState.size() << " taille" << std::endl;
	/*
	std::cout << state2->getPosition().i << "," <<state2->getPosition().j << " activé" << std::endl;
	std::cout << listStateNew[0]->getPosition().i << "," <<listStateNew[0]->getPosition().j << std::endl;
	std::cout << "state " << listState[0]->getActivity() << " stateNew " << listStateNew[0]->getActivity() << std::endl;
	listStateNew[0]->setActivity(true);
	std::cout << "state " << listState[0]->getActivity() << " stateNew " << listStateNew[0]->getActivity() << std::endl;
	*/				
	
	
	

//std::cout<<"deltaint [" << state2->getPosition().i << ", "<< state2->getPosition().j << "] " << state2->getVal() << " time: " << time << std::endl; 
		if(state2->getVal() == "0")//non brule
		{
			bool test = false;
			for(int x = 0;x<listState.size();x++)
			{
				if((listState[x]->getVal() == "1")||(listState[x]->getVal() == "2")) //chauffe brule
					test = true;
				
				
			}
			if (test)
				{
					state2new->setVal("1"); //chauffe
					state2new->setElapsed(time);
					//listStateNew[1]->setActivity(true);
					
					
					for(auto s : listStateNew)
			{
				//s->setActivity(true);
				//std::cout << s->getPosition().i << "," <<s->getPosition().j << " activé" << std::endl;
			}

					
					
				}
		}
		else if(state2->getVal() ==  "1") //chauffe
			{//std::cout << "elapsed time " << state2->getElapsed() << std::endl;
			for(auto s : listState)
			{
				//s->setActivity(true);
				//std::cout << s->getPosition().i << "," <<s->getPosition().j << " activé" << std::endl;
			}
			
				if(state2->getTemperature() >= t_ignition)
				{
					state2new->setVal("2"); //brule
				}
				else
				{
					e = time - state2->getElapsed();
					t = state2->getTemperature() + (k1 * (e*e*e*e)) + (k2 * e);
					
					//t = t_ambiente + (k1 * (time*time*time*time)) + (k2 * time);
					 
					state2new->setTemperature(t);
				}
				
			}
		else if(state2->getVal() ==   "2")//brule
			{
				if (state2->getMasse() <= m_extinction)
				{
				state2new->setVal("3");			//refroidi
				}else
				{
					t=0;
					//std::cout << "temperature ancien=" << state2->getTemperature() << " t=" << t << " time=" << time << std::endl; 
					//t = t_ambiente + ((k3 / m_extinction) * std::pow(state2->getTemperature(),2)) - (k3 * state2->getTemperature());
					
					//t = state2->getTemperature() - (k3 * state2->getTemperature() * state2->getTemperature());
					//std::cout << "temperature ancien=" << state2->getTemperature() << " t=" << t << " time=" << time << std::endl; 
					
					
					//t = state2->getTemperature() + ((k3 / m_extinction) * state2->getTemperature()* state2->getTemperature()) - (k3 * state2->getTemperature());
					t = t_ambiente + ((k3 / m_extinction) * state2->getTemperature()* state2->getTemperature()) - (k3 * state2->getTemperature());
					state2new->setTemperature(t);
					
				
					m = state2->getMasse() - k4 * state2->getlastMasse();
					//std::cout << "masse ancien=" << state2->getMasse() << " m=" << m << " time=" << time << "  " << state2->getlastMasse() << std::endl; 
					state2new->setMasse(m);
				}
				
			}
		else if(state2->getVal() ==  "3") //refroidi
		if(state2->getTemperature() <= t_ambiente)
		{
			state2new->setVal("4"); //finit
			
		}
		else
		{
			
			t = state2->getTemperature() - k5 * std::pow(state2->getTemperature(),2) - k6 * state2->getTemperature();
			state2new->setTemperature(t);
		}
		else if(state2->getVal() ==   "4") //finit
		{
			state2new->setActivity(false);
			}
		
//std::cout<<"deltaint [" << state2->getPosition().i << ", "<< state2->getPosition().j << "] " << state2->getVal() << " time: " << time<< std::endl;	
		

  }
  virtual void externalTransition(
            const vd::ExternalEventList& /*event*/,
            vle::devs::Time /*time*/) override
  {
  }
  virtual void confluentTransitions(
            vle::devs::Time time,
            const vd::ExternalEventList& events) override
  {
    internalTransition(time);
    externalTransition(events, time);
  }
  virtual std::unique_ptr<vle::value::Value> observation(
            const vd::ObservationEvent& /*event*/) const override
  {
     return vv::String::create("a string");
  }
  virtual void finish()
  {
	  
  }
  
  void majstate()
  {
	  state2->setState(state2new->getPosition().i,state2new->getPosition().j,state2new->getVal(), state2new->getTemperature(), state2new->getMasse(),state2new->getElapsed());
	state2->setActivity(state2new->getActivity());
	 
  }
  
  
  
  
  private:
 
 };
 

 
} // namespace
DECLARE_DYNAMICSCOMP(feu::NewCpp)
