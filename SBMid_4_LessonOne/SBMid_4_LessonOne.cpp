
#include <iostream>
#include <vector>
#include <string>

class Wheel;
class Engine;

class Vehicle
{
public:
	
	virtual std::ostream& print(std::ostream& out) const { return out; }

	friend std::ostream& operator<<(std::ostream& out, const Vehicle& vh) { return vh.print(out); }

	virtual ~Vehicle() {};
};

class WaterVehicle : public Vehicle
{
private:
	float Draft;

public:
	
	WaterVehicle(float ValueDraft = 0) : Draft(ValueDraft) {}
	
	float getDraft() const { return Draft; }

	std::ostream& print(std::ostream& out) const override
	{
		out << "WaterVehicle Draft: " << Draft << "\n";
		return out;
	}
};

//class Wheel
//{
//private:
//	float Diameter;
//
//public:
//	Wheel(float ValueDiameter = 0) : Diameter(ValueDiameter) {}
//
//	float getDiameter() const { return Diameter; }
//};
//
//class Engine
//{
//private:
//	float Power;
//
//public:
//	Engine(float ValuePower = 0) : Power(ValuePower) {}
//
//	float getPower() const { return Power; }
//};

class RoadVehicle : public Vehicle
{
private:
	float RideHeight;
	
public:
	
	RoadVehicle(float ValueRoadVehicle = 0): RideHeight(ValueRoadVehicle){}

	float getRideHeight() const { return RideHeight; }
};

class Bicycle : public RoadVehicle
{
private:
	const Wheel* BW1;
	const Wheel* BW2;
	
public:
	Bicycle() = delete;
	
	Bicycle(const Wheel& BWheel1,const Wheel& BWheel2, float BValue) : RoadVehicle(BValue)
	{
		BW1 = &BWheel1;
		BW2 = &BWheel2;
	}

	std::ostream& print(std::ostream& out) const override;
	
	~Bicycle(){}
};

class Car : public RoadVehicle
{
private:
	const Engine* CEngine;
	const Wheel* CW1;
	const Wheel* CW2;
	const Wheel* CW3;
	const Wheel* CW4;

public:
	Car() = delete;
	
	Car(const Engine& Power,const Wheel& CWheel1, const Wheel& CWheel2, const Wheel& CWheel3, const Wheel& CWheel4, float CValue) : RoadVehicle(CValue)
	{
		CEngine = &Power;
		CW1 = &CWheel1;
		CW2 = &CWheel2;
		CW3 = &CWheel3;
		CW4 = &CWheel4;
	}

	std::ostream& print(std::ostream& out)const override;
	
	float getPowerEngine() const; 
	~Car(){}
};

class Wheel
{
private:
	float Diameter;

public:
	Wheel(float ValueDiameter = 0) : Diameter(ValueDiameter) {}

	float getDiameter() const { return Diameter; }
};

class Engine
{
private:
	float Power;

public:
	Engine(float ValuePower = 0) : Power(ValuePower) {}

	float getPower() const { return Power; }
};

std::ostream& Bicycle::print(std::ostream& out) const
{
	out << "Bicycle Wheels: " << BW1->getDiameter() << " " << BW2->getDiameter() << " Ride height: " << RoadVehicle::getRideHeight() << "\n";
	return out;
}

std::ostream& Car::print(std::ostream& out)const 
{
	out << "Car Engine: " << CEngine->getPower() << " Wheels: " << CW1->getDiameter() << " " << CW2->getDiameter() << " " << CW3->getDiameter() << " " << CW4->getDiameter() << " Ride height: " << RoadVehicle::getRideHeight() << "\n";
	return out;
}

float Car::getPowerEngine() const { return CEngine->getPower(); }

float getHighestPower(std::vector<Vehicle*>& vec)
{
	Car* Temp = nullptr;
	float Power = 0;
	
	for (int i = 0; i < vec.size(); i++)
	{
		Temp = dynamic_cast<Car*>(vec[i]);
		if (Temp)
		{
			if (Temp->getPowerEngine() > Power)	Power = Temp->getPowerEngine();
		}
	}
	
	delete Temp;
	return Power;
}

int main()
{
	Car c(Engine(150), Wheel(17), Wheel(17), Wheel(18), Wheel(18), 150);

	std::cout << c << '\n';

	Bicycle t(Wheel(20), Wheel(20), 300);

	std::cout << t << '\n';

	std::vector<Vehicle*> v;

	v.push_back(new Car(Engine(150), Wheel(17), Wheel(17), Wheel(18), Wheel(18), 250));

	v.push_back(new Car(Engine(200), Wheel(19), Wheel(19), Wheel(19), Wheel(19), 130));

	v.push_back(new WaterVehicle(5000));

	for (int i = 0; i < v.size(); i++)
	{
		std::cout << "v[" << i << "]: " << *v[i];
	}

	std::cout << "The highest power is " << getHighestPower(v) << '\n';

	
	for (Vehicle* i : v) 
	{
		delete i;;
		v.pop_back();
		std::cout << "del v[" << v.size() << "]" << "\n";
	}

}

