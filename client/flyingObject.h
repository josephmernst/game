#ifndef _FLYING_OBJECT_H_
#define _FLYING_OBJECT_H_


class flyingObject{
 public:
  flyingObject();
  flyingObject(float* s);
  flyingObject(float* s, float* axis);
  flyingObject(float* s, float* axis, float* v);
  flyingObject(float* s, float* axis, float* v, float* a);
  ~flyingObject();
  
  void setPosition(float*);
  void setOrientation(float*);
  void setVelocity(float*);
  void setAcceleration(float*);
  
  void print(void);
 private:
  float* position;
  float* velocity;
  float* acceleration;
  float* orientation;  
};





#endif
