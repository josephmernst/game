#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <vector>
using namespace std;


class Object{
 public:
	Object();
	~Object();
	Object(const Object & orig);
	virtual void draw();
	void set_orientation(const double * orientation);
	void print_orientation();
	void move_forward(double x);
	void move_right(double x);
	void move_up(double x);
	void roll_right(double x);
	void turn_up(double x);
	bool selected;
	vector<double> get_position();
	
	double orientation[16];
	
 protected:
	void translate(double x, double y, double z);
	void rotate(double angle, double x, double y,double z);
	float min(float a, float b);
};

extern vector<Object *> objects;
#endif
