#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#define MAX_STATION 10

class Station
{
private:
    int subwayNum;
    int nodeNum;
    int nodeList;
    string name;

public:
    Station(int _subwayNum, int _nodeNum, int _nodeList, string _name) {
        subwayNum = _subwayNum;
        nodeNum = _nodeNum;
        nodeList = _nodeList;
        name = _name;
    }

    Station() {
        subwayNum = -1;
        nodeNum = -1;
        nodeList = -1;
        name = "";
    }
    int getNodeNum() {
        return nodeNum;
    }

    int getNodeList() {
        return nodeList;
    }

    int getSubwayNum() {
        return subwayNum;
    }

    string getSubwayName() {
        return name;
    }

    void setSubwayNum(int _subwayNum){
        subwayNum = _subwayNum;
    }

    void setNodeNum(int _nodeNum) {
        nodeNum = _nodeNum;
    }

    void setNodeList(int _nodeList) {
        nodeList = _nodeList;
    }

    void setName(string _name) {
        name = _name;
    }

    string getName() {
        return name;
    }
};

struct Node {
private:
    int id;
    int subwayNum;
    vector<string> str;
    vector<Station> log;

public:
    Node(int _id, vector<Station> _log) {
        id = _id;
        subwayNum = 0;
        log = _log;
    }
    Node() {
        id = -1;
        int subwayNum = -1;
    }
    ~Node() {};

    int getId() {
        return id;
    }

    string getNodeName() {
        string str = log[0].getSubwayName();
        return str;
    }

    int getNodeNum() {
        int n = 0;
        for (int i = 0; i < log.size(); i++) {
            n = log[i].getNodeNum();
        }
        return n;
    }

    int getLogSize() {
        return log.size();
    }

    vector<string> getLogName() {
        for (int i = 0; i < log.size(); i++) {
            str.push_back(log[i].getName());
        }

        return str;
    }

    void setSubwayNum(int _subwayNum) {
        subwayNum = _subwayNum;
    }

    void setId(int _id) {
        id = _id;
    }
    void setLog(int _subwayNum, int _nodeNum, int _nodeList, string _name) {
        Station temp(_subwayNum, _nodeNum, _nodeList, _name);
        log.push_back(temp);
    }
};
