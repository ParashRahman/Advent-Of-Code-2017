#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

struct xyz {
  long int x, y, z;

  xyz() : x(0), y(0), z(0) {}
  xyz(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}
  
  bool operator==(const xyz& other) {
    return x == other.x
      && y == other.y
      && z == other.z;
  }
};

struct Parabola {
  // f(a) = x*a^2 + y*a + z
  xyz coeffs;

  Parabola() : coeffs(0,0,0) {}
  Parabola(int _x, int _y, int _z) {
    coeffs.x = _x;
    coeffs.y = _y;
    coeffs.z = _z;
  }
  
  bool operator==(const Parabola& other) {
    return coeffs == other.coeffs;
  }
  
  bool operator>(const Parabola& other) {
    if (coeffs.x > other.coeffs.x) {
      return true;
    }
    if (coeffs.x == other.coeffs.x
	&& coeffs.y > other.coeffs.y) {
      return true;
    }
    if (coeffs.x == other.coeffs.x
	&& coeffs.y == other.coeffs.y
	&& coeffs.z > other.coeffs.z) {
      return true;
    }
    
    return false;
  }

  bool operator<(const Parabola& other) {
    return !((*this) == other) && !((*this) > other);
  }
}; 

struct Point {
  xyz p;
  xyz v;
  xyz a;
  int id;
  
  bool operator==(const Point& other) {
    return p == other.p
      && v == other.v
      && a == other.a;
  }
  
  bool operator>(const Point& other) {
    Parabola para_x, para_y, para_z,
      opara_x, opara_y, opara_z;
    para_x.coeffs = xyz(a.x, v.x, p.x);
    para_y.coeffs = xyz(a.y, v.y, p.y);
    para_z.coeffs = xyz(a.z, v.z, p.z);
    opara_x.coeffs = xyz(other.a.x, other.v.x, other.p.x);
    opara_y.coeffs = xyz(other.a.y, other.v.y, other.p.y);
    opara_z.coeffs = xyz(other.a.z, other.v.z, other.p.z);
    
    return false;
  } 
};

int main() {
  xyz parr[3];

  std::vector<Point> points;
  std::string pos, v, a;
  
  int i;
  int id = 0;
  while (std::cin >> pos >> v >> a) {
    Point poi;
    poi.id = id;
    ++id;
    std::string strpoints[3]; strpoints[0] = pos; strpoints[1] = v; strpoints[2] = a;
    for (int  j = 0; j < 3; ++j) {
      std::string x = "", y = "", z = "";
      std::string p = strpoints[j];
      
      for (i = 3; p[i] != ','; ++i) {
	x.push_back(p[i]);
      }
      ++i;
      for (; p[i] != ','; ++i) {
	y.push_back(p[i]);
      }
      ++i;
      for (; p[i] != '>'; ++i) {
	z.push_back(p[i]);
      }

      parr[j].x = std::stoi(x);
      parr[j].y = std::stoi(y);
      parr[j].z = std::stoi(z);

      switch (j) {
      case 0:
	poi.p = parr[j];
	break;
      case 1:
	poi.v = parr[j];
	break;
      case 2:
	poi.a = parr[j];
	break;
      }
 
    }

    // ensure positive acceleration
    if (poi.a.x < 0) {
      poi.a.x *= -1;
      poi.v.x *= -1;
      poi.p.x *= -1;
    }
    if (poi.a.y < 0) {
      poi.a.y *= -1;
      poi.v.y *= -1;
      poi.p.y *= -1;
    }
    if (poi.a.z < 0) {
      poi.a.z *= -1;
      poi.v.z *= -1;
      poi.p.z *= -1;
    }
    
    points.push_back(poi);
    
  }
  
  std::sort(points.begin(), points.end(),
	    [](const Point& p1, const Point& p2)->bool {
	      return
		Parabola(p1.a.x + p1.a.y + p1.a.z,
			 p1.v.x + p1.v.y + p1.v.z,
			 p1.p.x + p1.p.y + p1.p.z) <
		Parabola(p2.a.x + p2.a.y + p2.a.z,
			 p2.v.x + p2.v.y + p2.v.z,
			 p2.p.x + p2.p.y + p2.p.z);
	    });
  
  for (Point p : points){
    std::cout << p.id << std::endl;
  }
}

/**

          a1*x^2 + b1*x + c1 
       - (a2*x^2 + b2*x + c2)
-----------------------------
(a1-a2)*x^2+(b1-b2)*x+(c1-c2)

 **/
