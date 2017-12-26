#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <vector>

struct xyz {
  long long x, y, z;

  xyz() : x(0), y(0), z(0) {}
  xyz(long _x, long _y, long _z) : x(_x), y(_y), z(_z) {}
  
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
  Parabola(long _x, long _y, long _z) {
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
  long id;
  
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

void remove_same_positions(std::vector<Point>& points) {
  std::set<long> to_remove;
  for (long p1 = 0; p1 < points.size(); ++p1) {
    for (long p2 = p1 + 1; p2 < points.size(); ++p2) {
      if (points[p1].p == points[p2].p) {
	to_remove.insert(p1);
	to_remove.insert(p2);
      }
    }
  }

  for (auto it = to_remove.rbegin(); it != to_remove.rend(); ++it) {
    long dex = *it;
    Point temp = points[points.size()-1];
    points[points.size()-1] = points[dex];
    points.pop_back();
    points[dex] = temp;
  }
}

int main() {
  xyz parr[3];

  std::vector<Point> points;
  std::string pos, v, a;
  
  long i;
  long id = 0;
  while (std::cin >> pos >> v >> a) {
    Point poi;
    poi.id = id;
    ++id;
    std::string strpoints[3]; strpoints[0] = pos; strpoints[1] = v; strpoints[2] = a;
    for (long j = 0; j < 3; ++j) {
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
    /*    if (poi.a.x < 0) {
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
    */
    points.push_back(poi);
    
  }

  std::cout << points.size() << std::endl;

  // simulate particles
  for (long iter = 0; iter < 100000; ++iter) {
    remove_same_positions(points);
    for (Point& p : points) {
      p.v.x += p.a.x;
      p.v.y += p.a.y;
      p.v.z += p.a.z;
      p.p.x += p.v.x;
      p.p.y += p.v.y;
      p.p.z += p.v.z;
    }
    if (iter % 1000 == 0) {
      std::cout << "iter " << iter << std::endl;
      std::cout << points.size() << std::endl;
      
    }
  }
  std::cout << points.size() << std::endl;

}
