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
const double ksi[] { 1/2., 0., 1/2. };
const double n[] {1/2., 1/2., 0.};
const double w[] {1/3., 1/3., 1/3.};

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
  points[2] = Normalize(c, a, b, ksi[2], n[2]);
  
  return points;
}
/* jakobian przekształcenia*/
double Jakobian (Point a, Point b, Point c)
{
  double result = (b.x - a.x) *(c.y - a.y) - (c.x - a.x) * (b.y - a.y);
  return result > 0 ? result : (-1)*result;
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
  return J * (normP.x+3*normP.y-1);
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

void calculateIntegralSeq(Point a, Point b, Point c)
{
  printPoints(new Point[3]{a, b, c}, "Przed normalizacją");
  Point *norA = NormalizeTriangle(a, b, c);
  printPoints(norA, "Normalizacja");
  
  double J = Jakobian(a, b, c);
  cout << "Jakobian: " << J << endl;
  
  double *FResult = new double[3];
   FResult[0] = F(J, norA[0]);
   FResult[1] = F(J, norA[1]);
   FResult[2] = F(J, norA[2]);
   cout << "Zastosowana funkcji podcałkowej: " << endl;
   cout << FResult[0] << " " << FResult[1] << " " << FResult[2] << endl;
  
   /* obliczanie całki podówjnej */
   double dbIntegral = 0;
   for(int i = 0; i < 3; i++)
   {
     dbIntegral += FResult[i]*w[i];
   }
   dbIntegral = dbIntegral/2.;
   cout<<"Wynik: " << dbIntegral << "."<< endl;	
}

int main() {
  //Przyklad testowy:
  Point a = {1,1}; Point b = {3,2}; Point c = {2,3}; Point d = {3,1};
  /*Wczytywanie wejścia */
  cout<<"Podaj 4 punkty w taki sposób, że wsółrzędne x,y oddziel spacją i nacisnije enter.";
  cout<<"Punkt A:";
  cin>>a.x>>a.y;
  cout<<"Punkt B:";
  cin>>b.x>>b.y;
  cout<<"Punkt C:";
  cin>>c.x>>c.y;
  cout<<"Punkt D:";
  cin>>d.x>>d.y;
  
  //Można zmienić kolejnośc jeśli ma znaczenie(?).
  cout<<endl<< "========================================"<<endl;
  cout<<"Trójkąt: ABC" <<endl;
  calculateIntegralSeq(a, b, c);
  cout<<endl<< "========================================"<<endl;
  cout<<"Trójkąt: CDA" <<endl;
  calculateIntegralSeq(c, d, a);
  return 0;
}
