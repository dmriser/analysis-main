
#include "TLorentzVector.h"
#include "PhysicsEvent.h"

#ifndef physics_event_builder_h
#define physics_event_builder_h

class PhysicsEventBuilder{

 public:
  PhysicsEventBuilder();
  PhysicsEventBuilder(TLorentzVector beam, TLorentzVector target);
  ~PhysicsEventBuilder();

 private:
  PhysicsEvent physicsEvent; 

  void setVectors(TLorentzVector &electron);
  void setKinematics();
  
 public:
  PhysicsEvent &getPhysicsEvent(TLorentzVector &detectedElectron);
  PhysicsEvent &getPhysicsEvent(TLorentzVector &detectedElectron, TLorentzVector &detectedParticle);
  PhysicsEvent &getPhysicsEvent(TLorentzVector &detectedElectron, TLorentzVector &detectedParticle1, TLorentzVector &detectedParticle2);
  PhysicsEvent &getPhysicsEvent(TLorentzVector &detectedElectron, TLorentzVector &detectedParticle1, TLorentzVector &detectedParticle2, TLorentzVector &detectedParticle3);

};

#endif
