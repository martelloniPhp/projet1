/*
* @@tagdynamic@@
* @@tagdepends:@@endtagdepends
*/
#include <vle/value/Value.hpp>
#include <vle/devs/DynamicsComp.hpp>
#include <fstream>
#include <algorithm>

namespace vd = vle::devs;
namespace vv = vle::value;
namespace feu {
class NewCpp_1 : public vd::DynamicsComp
{
 public:
  NewCpp_1(const vd::DynamicsCompInit& init,
                const vd::InitEventList& events)
        : vd::DynamicsComp(init, events)
  {
 
  }
  virtual ~NewCpp_1()
  {
  }
  virtual vd::Time init(vle::devs::Time time) override
  {
   initprint();
   
    return 0;
  }
  virtual void output(vle::devs::Time time,
                      vd::ExternalEventList& /*output*/)  override
  {
	  // std::cout<<"output dyn1 time: "<< time << std::endl;
	   
	   
	     printTemp(time);
		printMass(time);
		printHeatmap(time, "/home/martelloni/model/feuResultat/img/heatmap.csv");
		printActivity(time,"/home/martelloni/model/feuResultat/activity.csv");
		
		
		
		
	
	   
	   
  }
  virtual vd::Time timeAdvance() const override
  {
	 //sstd::cout<<"timeadvence = 15: "<< time << std::endl;
    return 1;
  }
  virtual void internalTransition(vle::devs::Time time) override
  {
	  //std::cout<<"deltaint dyn1"<< std::endl;
	 // print(time,"/home/martelloni/model/feuResultat/testFeu2.txt");
	 // print2("/root/test3",time);
	  //print3(); 
	  
	
	
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
    return 0;
  }
  virtual void finish()
  {
	 //print2("/root/test3");
	 //print3("/root/IHMPH/file1");
  }
  

	
	void printTemp(int time)
  {
	   for(auto s: influanceur)
	{
	  if((s.second->getPosition().i==10)&&(s.second->getPosition().j==10))
	{
	  std::ofstream fichier("/home/martelloni/model/feuResultat/tempFeu.csv", std::ios::out | std::ios::app);  // ouverture en écriture avec effacement du fichier ouvert

 

        if(fichier)

        {

               

                //fichier <<"Etat: " << influanceur[i]->getVal() <<"temperature: " << influanceur[i]->getTemperature()  <<" time: "<< time << std::endl; 
                fichier << time <<";"<< s.second->getTemperature()  << std::endl; 

               
 

                fichier.close();

        }

        else

                std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
  }
  }
}
	
	
		void printMass(int time)
  {
	    for(auto s: influanceur)
	{
	  if((s.second->getPosition().i==10)&&(s.second->getPosition().j==10))
	{
	  std::ofstream fichier("/home/martelloni/model/feuResultat/massFeu.csv", std::ios::out | std::ios::app);  // ouverture en écriture avec effacement du fichier ouvert

 

        if(fichier)

        {

               

                //fichier <<"Etat: " << influanceur[i]->getVal() <<"masse: " << influanceur[i]->getMasse()  <<" time: "<< time << std::endl; 
				fichier << time <<";"<< s.second->getMasse()  << std::endl; 

               
 

                fichier.close();

        }

        else

                std::cerr << "Impossible d'ouvrir le fichier !" << std::endl;
  }
  }
}
	void printHeatmap(int time, std::string path)
	{
		 
		// if((time == 25)|| (time == 50) || (time == 100) || (time == 150))
		 //{
			 std::string file = path + std::to_string (time);
		 std::ofstream fichier(file, std::ios::out | std::ios::app);  // ouverture en écriture avec effacement du fichier ouvert

         if(fichier)

        {

               

               
   for(int i =0;i<influance.size();i++)
	{
	if(influance[i]->getPosition().j==0)
			fichier << std::endl;
	//fichier << 	influanceur[i]->getVal() << "("<< time <<")"  << ";"; 
	fichier << 	influance[i]->getTemperature()  << ";"; 	
               
 }

 //for(auto s: influanceur)
 /*for (auto s =influanceur.begin();s!=influanceur.end();s++)
 {
	 if(s->second->getPosition().j==0)
			fichier << std::endl;
	fichier << 	s->second->getTemperature()  << ";"; 		
 }
 * */
 
 
fichier << std::endl;

                fichier.close();
	}
//}
}





	void printActivity(int time, std::string path)
	{
		 
		 if((time == 0)|| (time == 1)||(time == 2)||(time == 3))
		 {
			 std::string file = path + std::to_string (time);
		 std::ofstream fichier(file, std::ios::out | std::ios::app);  // ouverture en écriture avec effacement du fichier ouvert

         if(fichier)

        {

               

               
 /*  for(int i =0;i<influanceur.size();i++)
	{
	if(influanceur[i]->getPosition().j==0)
			fichier << std::endl;
	//fichier << 	influanceur[i]->getVal() << "("<< time <<")"  << ";"; 
	fichier << 	influanceur[i]->getActivity()  << ";"; 	
               
 }*/
 
  for(auto s: influanceur)
 {
	 if(s.second->getPosition().j==0)
			fichier << std::endl;
	fichier << 	s.second->getActivity()  << ";"; 		
 }
fichier << std::endl;

                fichier.close();
	}
}
}
	void initprint()
	{
/*		FILE * pFile;
  int buffer[] = {100,100};
  pFile = fopen ("/root/IHMPH/file1", "wb");
  fwrite (buffer , sizeof(int), 2, pFile);
  fclose (pFile);*/
std::ofstream ofs;
ofs.open("/home/martelloni/model/feuResultat/massFeu.csv", std::ofstream::out | std::ofstream::trunc);
ofs.close();
ofs.open("/home/martelloni/model/feuResultat/tempFeu.txt", std::ofstream::out | std::ofstream::trunc);
ofs.close();
ofs.open("/home/martelloni/model/feuResultat/tempFeu.csv", std::ofstream::out | std::ofstream::trunc);
ofs.close();
ofs.open("/home/martelloni/model/feuResultat/testFeu2.txt", std::ofstream::out | std::ofstream::trunc);
ofs.close();
ofs.open("/home/martelloni/model/feuResultat/testFeu.txt", std::ofstream::out | std::ofstream::trunc);
ofs.close();
ofs.open("/home/martelloni/model/feuResultat/heatmap.csv", std::ofstream::out | std::ofstream::trunc);
ofs.close();
ofs.open("/home/martelloni/model/feuResultat/heatmap.csv0", std::ofstream::out | std::ofstream::trunc);
ofs.close();
ofs.open("/home/martelloni/model/feuResultat/heatmap.csv25", std::ofstream::out | std::ofstream::trunc);
ofs.close();
ofs.open("/home/martelloni/model/feuResultat/heatmap.csv50", std::ofstream::out | std::ofstream::trunc);
ofs.close();
ofs.open("/home/martelloni/model/feuResultat/heatmap.csv100", std::ofstream::out | std::ofstream::trunc);
ofs.close();
ofs.open("/home/martelloni/model/feuResultat/heatmap.csv150", std::ofstream::out | std::ofstream::trunc);
ofs.close();
ofs.open("/home/martelloni/model/feuResultat/heatmap.csv200", std::ofstream::out | std::ofstream::trunc);
ofs.close();
ofs.open("/home/martelloni/model/feuResultat/heatmap.csv250", std::ofstream::out | std::ofstream::trunc);
ofs.close();
ofs.open("/home/martelloni/model/feuResultat/heatmap.csv300", std::ofstream::out | std::ofstream::trunc);
ofs.close();
ofs.open("/home/martelloni/model/feuResultat/activity.csv0", std::ofstream::out | std::ofstream::trunc);
ofs.close();
ofs.open("/home/martelloni/model/feuResultat/activity.csv1", std::ofstream::out | std::ofstream::trunc);
ofs.close();
ofs.open("/home/martelloni/model/feuResultat/activity.csv2", std::ofstream::out | std::ofstream::trunc);
ofs.close();
ofs.open("/home/martelloni/model/feuResultat/activity.csv3", std::ofstream::out | std::ofstream::trunc);
ofs.close();
ofs.open("/home/martelloni/model/feuResultat/activityNew.csv0", std::ofstream::out | std::ofstream::trunc);
ofs.close();
ofs.open("/home/martelloni/model/feuResultat/activityNew.csv1", std::ofstream::out | std::ofstream::trunc);
ofs.close();
ofs.open("/home/martelloni/model/feuResultat/activityNew.csv2", std::ofstream::out | std::ofstream::trunc);
ofs.close();
ofs.open("/home/martelloni/model/feuResultat/activityNew.csv3", std::ofstream::out | std::ofstream::trunc);
ofs.close();
	}
	

  
 };
} // namespace
DECLARE_DYNAMICSCOMP(feu::NewCpp_1)
