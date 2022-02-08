#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <array>

template <typename T>
using Vector = std::vector<T>;
typedef std::string String;
typedef std::array<double, 3> Ray;
typedef std::array<double, 2> Pos;
struct Surface
{
	Pos pos1;
	Pos pos2;
	bool isDetector = false;
};

using std::tan;
using std::atan;
using std::cos;
using std::sin;
using std::cout;
using std::cin;
using std::sqrt;
using std::to_string;
using std::floor;

Vector<Ray> particles;

constexpr double PI{4 * atan(1)};

const Vector<Pos> SOURCES{{-5.0, 0.0}};
//const Vector<Pos> SOURCES{{-5.0, 0.0}, {-5.0, 1.0}, {-5.0, -1.0}};	// Any number of particle sources go here
const double DTHETA = 0.19634954;					// Difference between max and min angle in radians of particle vel from each source
const double PART_PER_SOURCE = 100;					// Number of particles per source
const double GRATING_X = 0.0;						// x position of grating
const double GRATING_DX = 0.8;						// thickness of grating
const double DETECTOR_X = 1.0;						// x position of detector

const double SLIT1_Y1 = 1.99;						// slit 1 is between y1 and y2
const double SLIT1_Y2 = 1.01;

const double SLIT2_Y1 = -1.01;						// slit 2 is between y1 and y2
const double SLIT2_Y2 = -1.99;

Vector<Pos> det_pos;

Vector<Surface> surfaces{{{-5.0, 0.5}, {15.0, 0.5}}, {{-5.0, -0.5}, {15.0, -0.5}}, {{15.0, 0.5}, {15.0, -0.5}, true}};
/*
Vector<Surface> surfaces{{{GRATING_X, 10}, {GRATING_X, SLIT1_Y1}},
			{{GRATING_X, SLIT1_Y1}, {GRATING_X + GRATING_DX, SLIT1_Y1}},
			{{GRATING_X, SLIT1_Y2}, {GRATING_X + GRATING_DX, SLIT1_Y2}},
			{{GRATING_X, SLIT1_Y2}, {GRATING_X, SLIT2_Y1}},
			{{GRATING_X, SLIT2_Y1}, {GRATING_X + GRATING_DX, SLIT2_Y1}},
			{{GRATING_X, SLIT2_Y2}, {GRATING_X + GRATING_DX, SLIT2_Y2}},
			{{GRATING_X, -10}, {GRATING_X, SLIT2_Y2}},
			{{DETECTOR_X, 10}, {DETECTOR_X, -10}, true}};
*/

String print(Ray r)
{
	String s = "(" + to_string(r[0]) + ", " + to_string(r[1]) + ", " + to_string(r[2]) + ")";
	return s;
}

String print(Pos p)
{
	String s = "(" + to_string(p[0]) + ", " + to_string(p[1]) + ")";
	return s;
}

double sqr(double d){return std::pow(d, 2);}

bool equal(Ray r, Pos p){return r[0] == p[0] && r[1] == p[1];}

bool equal(Pos p1, Pos p2){return p1[0] == p2[0] && p1[1] == p2[1];}

bool equal(Pos p, Ray r){return r[0] == p[0] && r[1] == p[1];}

bool larger(double x, double y)
{
	double xa = x > 0? x: -x;
	double ya = y > 0? y: -y;
	return xa > ya;
}

double distance(Ray r, Pos p)
{
	return sqrt(sqr(r[0] - p[0]) + sqr(r[1] - p[1]));
}

double distance(Pos p, Ray r)
{
	return sqrt(sqr(r[0] - p[0]) + sqr(r[1] - p[1]));
}

double getAngle(double x, double y)
{
	bool f1 = x < 0;
	bool f2 = y < 0;
	double th = 0.0;
	if(larger(x, y))
	{
		th = atan(y / x);
		if(f1)
			th = th > 0? th - PI: th + PI;
	}
	else
	{
		th = PI / 2 - atan(x / y);
		if(f2)
			th = th - PI;
	}
	return th;
}

void simulate(Ray &r)
{
	bool done = false;
	while(!done)
	{
		cout << print(r) << "--";
		Surface best_coll_surf{{0.0, 0.0}, {0.0, 0.0}, false};
		Pos best_coll_point;
		double best_coll_dist = -1;
		for(auto s: surfaces)
		{
			if(!equal(r, s.pos1) && !equal(r, s.pos2))
			{
				double dx{s.pos1[0] - r[0]};
				double dy{s.pos1[1] - r[1]};
				double theta1 = getAngle(dx, dy);
				dx = s.pos2[0] - r[0];
				dy = s.pos2[1] - r[1];
				double theta2 = getAngle(dx, dy);
				if(theta1 < theta2)
				{
					double thT = theta1;
					theta1 = theta2;
					theta2 = thT;
				}
				if(theta1 - theta2 != PI && theta1 >= r[2] && r[2] >= theta2)
				{
					double dx = s.pos1[0] - s.pos[0];
					double dy = s.pos1[1] - s.pos[1];
					if(dy * cos(r[2]) != dx * sin(r[2]))
					{
						Pos coll_pt{}
					}
					Pos coll_pt{s.pos2[0] + thr * (s.pos1[0] - s.pos2[0]), s.pos2[1] + thr * (s.pos1[1] - s.pos2[1])};
					if(best_coll_dist == -1)
					{
						best_coll_surf = s;
						best_coll_point = coll_pt;
						best_coll_dist = distance(r, coll_pt);
					}
					else
					{
						double coll_dist = distance(r, coll_pt);
						if (coll_dist < best_coll_dist && coll_dist > 0)
						{
							best_coll_surf = s;
							best_coll_point = coll_pt;
							best_coll_dist = coll_dist;
						}
					}
				}
			}
		}
		if(best_coll_dist == -1)
		{
			done = true;
		}
		else if(best_coll_surf.isDetector)
		{
			done = true;
			det_pos.push_back(best_coll_point);
			cout << print(best_coll_point);
		}
		else
		{
			double thn = 0;
			if(best_coll_surf.pos1[0] == best_coll_surf.pos2[0])
			{
				thn = r[2] > 0? PI - r[2]: -PI - r[2];
			}
			else if(best_coll_surf.pos1[1] == best_coll_surf.pos2[1])
			{
				thn = -r[2];
			}
			else
			{
				cout << "YOOO";
				double dx = best_coll_surf.pos1[0] - best_coll_surf.pos2[0];
				double dy = best_coll_surf.pos1[1] - best_coll_surf.pos2[1];
				if(dx < 0)
				{
					dx = -dx;
					dy = -dy;
				}
				double ths = getAngle(dx, dy);
				thn = 2 * ths - thn;
				if(thn > PI)
				{
					thn = thn - PI;
				}
				else if(thn < -PI)
				{
					thn = thn + PI;
				}
			}
			r[2] = thn;
			r[0] = best_coll_point[0];
			r[1] = best_coll_point[1];
		}
	}
	cout << "\n";
}

void populate()
{
	for(auto source: SOURCES)
	{
		for(int j{}; j < PART_PER_SOURCE; j++)
		{
			Ray r = {source[0], source[1], DTHETA * (j / PART_PER_SOURCE - 0.5)}; // evenly distr through angles from source
			particles.push_back(r);
		}
	}
}

int main()
{
	populate();
	for(int i{}; i < particles.size(); i++)
	{
		simulate(particles[i]);
	}
	cout << "All detected collision points: \n";
	for(Pos p: det_pos)
	{
		cout << print(p) << ", ";
	}
	cout << "\n";
	cout << "View y-coord distribution? [y/n] ";
	char c;
	cin >> c;
	if(c == 'y')
	{
		cout << "Number of lots? They will be centered around y = 0. ";
		String s;
		cin >> s;
		int lots = std::stoi(s);
		cout << "Max dy? ";
		cin >> s;
		double max_dy = std::stod(s);
		int distr[lots]{};
		int out_range = 0;
		for(Pos p: det_pos)
		{
			double y = p[1];
			int lot = (int) floor((p[1] + max_dy) * lots / (2 * max_dy));
			if(lot >= 0 && lot < lots)
			{
				distr[lot]++;
			}
			else
			{
				out_range++;
			}
		}
		int i = 0;
		bool done = false;
		for(int c = 0; c < lots; c++)
		{
			cout << '-';
		}
		cout << '\n';
		while(!done)
		{
			done = true;
			for(int c = 0; c < lots; c++)
			{
				if(distr[c] > i)
				{
					done = false;
					cout << '*';
				}
				else
				{
					cout << ' ';
				}
			}
			cout << '\n';
			i++;
		}
		cout << "\n\n" << out_range << " values were out of range.";
	}
}

