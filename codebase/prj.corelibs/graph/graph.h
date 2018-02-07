///
///@file dummy/dummy.h
///@authors Panchenko A.V.
///@brief Dummy class for Core  libs
///


#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <Eigen/Dense>
#include <Eigen/Geometry>

#include <vector>
#include <map>
#include <iostream>

#include <pose/pose.h>

using namespace std;
using namespace Eigen;


struct Vertex {

  typedef pair<Pose, Vertex*> ve;
  vector<ve> adj;
  bool used;
  string name;
  Pose pose;
  Vertex(const string s, const Pose p) : name(s), pose(p) {}
};





class Graph{
public: 
  Graph();
  ~Graph();

  typedef map<string, Vertex *> vmap; // ���������� ����� ��� ������
  vmap g; //������� ����� �������� �����



  void addVertex(const string&, const Pose& pose); //��������� �������
  void addEdge(const string& from, const string& to, const Pose& pose); //��������� �����
  void addBidirectional(const string& from, const string& to, const Pose& pose); //��������� ��������������� �����

  void DFS(const string name); //����� ����� �� ���� �������

  Pose DFS(const string from, const string to, Pose = Pose()); // ������� Pose �� ������� from � ������� to

  void setNotUsed(); // ���������� ������� �� �����������

};

#endif