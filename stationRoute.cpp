#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Graph.h"

using namespace std;
vector<int> line;
bool visited[10];
vector<int> graph[10];
vector<int> route;

vector<pair<int, int>> graph_[10];

vector<int> dfs(int x, int goal) {
    visited[x] = true;

    line.push_back(x);

    if (x == goal) {
        int count = line.size();

        for (int i = 0; i < count; i++) {
            route.push_back(line[i]);
        }
    }

    for (int i = 0; i < graph_[x].size(); i++) {
        int y = graph_[x][i].first;
        if (!visited[y]) {
            dfs(y, goal);
            visited[y] = false;
        }
    }
    line.pop_back();
    return route;
}


int main() {
    //그래프 생성
    vector<Node> node;
    vector<Station> log;
    int sub[] = { 0, 2, 3, 1, 2, 3, 1, 0, 0, 0 };

    //노드에 정보입력
    for (int i = 0; i < 10; i++) {
        node.push_back(Node(i, log));
        node[i].setSubwayNum(sub[i]);
    }

    //int 그래프 연결(인접리스트)
    graph_[1].push_back(make_pair(7, 2));
    graph_[2].push_back(make_pair(7, 3));
    graph_[3].push_back(make_pair(8, 1));
    graph_[4].push_back(make_pair(8, 2));
    graph_[5].push_back(make_pair(9, 3));
    graph_[6].push_back(make_pair(9, 1));

    graph_[7].push_back(make_pair(1, 2));
    graph_[7].push_back(make_pair(2, 3));
    graph_[7].push_back(make_pair(8, 2));
    graph_[7].push_back(make_pair(9, 3));

    graph_[8].push_back(make_pair(3, 1));
    graph_[8].push_back(make_pair(4, 2));
    graph_[8].push_back(make_pair(7, 2));
    graph_[8].push_back(make_pair(9, 1));

    graph_[9].push_back(make_pair(5, 3));
    graph_[9].push_back(make_pair(6, 1));
    graph_[9].push_back(make_pair(7, 3));
    graph_[9].push_back(make_pair(8, 1));

    Station start, arr, transfer;
    string tmp1, tmp2;

    cout << "==============================================" << endl << endl << "** 주의사항 **" << endl << endl << "1. 띄어쓰기나 호선을 입력하지 않습니다" << endl << "2. '역'은 기입하지 않고 역의 이름만 입력합니다" << endl << "   (ex.대구역(X), 대구(O))" << endl << "3. 출발역과 도착역을 순서에 맞게 하나씩 입력합니다" << endl << "4. 이름이 바르게 입력되었는지 확인합니다." << endl << endl << "==============================================" << endl << endl;
    cout << "출발역을 입력해주세요 : ";
    cin >> tmp1;
    start.setName(tmp1);

    cout << "도착역을 입력해주세요 : ";
    cin >> tmp2;
    arr.setName(tmp2);
    cout << endl;

    ifstream fin, fin2, fin3;
    string line, name;
    int subwayNum, nodeNum, nodeList;

    fin.open("subway.txt");

    if (!fin.is_open()) {
        cout << "경로 파일이 존재하지 않습니다." << endl;
    }

    int count = 1;

    while (getline(fin, line)) {
        istringstream buffer(line);

        buffer >> subwayNum >> nodeNum >> nodeList >> name;

        if (nodeNum == count) {
            node[count].setLog(subwayNum, nodeNum, nodeList, name);
        }

        if (subwayNum == 0)
            count++;

        if (name == arr.getName()) {
            arr.setSubwayNum(subwayNum);
            arr.setNodeNum(nodeNum);
            arr.setNodeList(nodeList);
        }

        if (name == start.getName()) {
            start.setSubwayNum(subwayNum);
            start.setNodeNum(nodeNum);
            start.setNodeList(nodeList);
        }
    }

    vector<int> route_;

    //같은 배열에만 존재할 경우
    int stationCnt, lineNum, lineTmp, tmp;
    int total = 0;
    int trans = 0;
    vector<string> route_name;
    //vector<int> route_num;

    if (start.getNodeNum() == arr.getNodeNum()) {
        stationCnt = abs(start.getNodeList() - arr.getNodeList());

        cout << start.getName() << "역(" << start.getSubwayNum() << "호선) - " << arr.getName() << "역(" << arr.getSubwayNum() << "호선) :" << stationCnt << "역, " << stationCnt * 2 << "분 소요" << endl;
    }

    else {
        route_ = dfs(node[start.getNodeNum()].getId(), node[arr.getNodeNum()].getId());

        for (int i = 0; i < route_.size(); i++)
        {
            if (route_[i] == node[start.getNodeNum()].getId())
            {
                total += abs(start.getNodeList() - node[start.getNodeNum()].getLogSize());
                continue;
            }

            if (route_[i] == node[arr.getNodeNum()].getId())        //도착지점
            {
                total += (node[arr.getNodeNum()].getLogSize() - arr.getNodeList());

                cout << start.getName() << "(" << start.getSubwayNum() << "호선) - ";
                
                for (int j = 0; j < graph_[route_[i]].size() + 1; j++) {     
                    if (graph_[route_[i-1]][j].first == route_[i])
                       tmp = j;
                }
                for (int j = 0; j < route_name.size(); j++) {
                    if (graph_[route_[j]][tmp].second != graph_[route_[j + 1]][tmp].second) {
                        cout << route_name[j] << "(환승 " << graph_[route_[j]][tmp].second << "호선) - ";
                        trans++;
                    }  
                }

                cout << arr.getName() << "(" << arr.getSubwayNum() << "호선) :" << total << "역, " << trans<< " 환승, " << (total * 2) + (trans * 8) << "분 소요" << endl;

                vector<string>().swap(route_name);
                //vector<int>().swap(route_num);
                total = 0;
                trans = 0;

                continue;
            }
            //total++;
            total += node[route_[i]].getLogSize();
            if (route_[i - 1] == 7 && route_[i] == 8)
                total--;
            route_name.push_back(node[route_[i]].getNodeName());
            //route_num.push_back(route_[i]);
        }
    }
}