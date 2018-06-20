#include <iostream>
using namespace std;

/* Całka podówjna po trójkącie */

/* Struktura Point */
struct Point
{
  double x;
  double y;
};

/* Współrzędne i wagi punktów Gaussa dla 3 punktów
    ksi (ξ), n współrzędnbe punktów Gaussa
    w       wagi punktów Gaussa
    n       ilości punktów Gauusa
 mamy trzy punkty więc skorzystam z trzech elementowych tablic,
 i-ty element w tablicy będzie wykorzystany przy oblcizeniach i-tego punktu. 
 strona 9 -> http://www.imio.polsl.pl/Dopobrania/calkowanie_2.pdf
 możesz to dostosować do sowich potrzeb
*/
const double ksi[] { 1/2, 0, 1/2 };
const double n[] {1/2, 1/2, 0};
const double w[] {1/3, 1/3, 1/3};

/*
Funkcja normalizująca punkty trojkąta.
str 6 -> http://www.imio.polsl.pl/Dopobrania/calkowanie_2.pdf
*/

Point Normalize(Point p1, Point p2, Point p3ref, double ksi, double n)
{
  Point newPoint;
  newPoint.x = p1.x + (p2.x - p1.x) * ksi + (p3ref.x - p1.x) * n;
  newPoint.y = p1.y + (p2.y - p1.y) * ksi + (p3ref.y - p1.y) * n;
  return newPoint;
}

Point *NormalizeTriangle(Point a, Point b, Point c)
{
  Point *points =new Point[3] {
  	{0, 0},
  	{0, 0},
  	{0, 0}
  };
  
  points[0] = Normalize(a, b, c, ksi[0], n[0]);
  points[1] = Normalize(b, c, a, ksi[1], n[1]);
  points[2] = Normalize(c, a, c, ksi[2], n[2]);
  
  return points;
}
/* jakobian przekształcenia*/
double Jakobian (Point a, Point b, Point c)
{
  return (b.x - a.x) *(c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}
/* Funkcja podcałkowa dla trójkąta znormalizowange. */
/* x + 3y - 1 */
double F(double J, Point normP)
{
  /*return Point
  {
    J * normP.x,
    J * normP.y
  };
  */
  return J* (normP.x+3*normP.y-1);
}

void printPoints(Point *points, string label)
{ 
  cout <<label << endl;
  for(int i = 0; i < 3; i++)
  {
  cout << "Point " << i+1 << ": (";
  cout << points[i].x << ", ";
  cout << points[i].y << ")" << endl;
  }
}
int main() {
  Point a = {1,1}; Point b = {3,2}; Point c = {2,3};
  
  Point *norA = NormalizeTriangle(a, b, c);
  printPoints(norA, "Normalizacja");
  
  double J = Jakobian(a, b, c);
  cout << "Jakobian: " << J << endl;
  
  Point *pointsF =new Point[3] {
  	{0, 0},
  	{0, 0},
  	{0, 0}
  };
   pointsF[0] = F(J, norA[0]);
   pointsF[1] = F(J, norA[1]);
   pointsF[2] = F(J, norA[2]);
   printPoints(pointsF, "Zastosowana funkcja podcałkowa");
  
   obliczanie całki podówjnej
   double = dbIntegral;
   for(int i = 0; i < 3; i++)
   {
     dbIntegral += pointsF[i]*w[i];
   }
   cout<<"Wynik: " << dbIntegral << "."<< endl;
  return 0;
}
