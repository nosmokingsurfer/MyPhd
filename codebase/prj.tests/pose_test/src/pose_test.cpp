// single_leg_test.cpp : Defines the entry point for the console application.
//

#include <pose/pose.h>


using namespace std;
using namespace Eigen;


int main(int argc, char** argv)
{
  Vector3d t(1,2,3);
  Vector3d angles(EIGEN_PI/4, 0, 0);

  Pose temp(angles, t);

  Vector3d original(1,0,0);
  cout << "original = " << original.transpose() << endl;

  Vector3d result(0,0,0);

  result = temp.T*original;  //������ original � ������� ��������� temp ����� ����� ���������� result

  cout << "result = " << result.transpose() << endl;

	 return 0;
}

