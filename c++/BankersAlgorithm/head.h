#ifndef __HEAD_H__
#define __HEAD_H__


#include <vector>
#include <iostream>
using namespace std;



//进程对象
//
//  每个对象都是一个进程
//  进程里面保存有自己的  max need  allocation request
//
class Process
{
public:
    //
    Process()
    {}

    //vector的大小应该与资源数相同
    void initValue(int resourcesnum)
    {
        _max.resize(resourcesnum);
        _allocation.resize(resourcesnum);
        _need.resize(resourcesnum);
     //   _request.reserve(resourcesnum);
    }

    //输入一开始的各进程的资源情况 // 
    void setValue()
    {
        //max
        cout << "请输入_max：";
        for (auto& e : _max) {
            cin >> e;
        }

        //allocation
        cout << "请输入_allocation：";
        for (auto& e : _allocation) {
            cin >> e;
        }
        
        //need
        for (size_t i = 0; i < _max.size(); ++i) {
            _need[i] = _max[i] - _allocation[i];
        }

    }

    //输出本进程的信息
    void printValue()
    {
        //max
        for (auto e : _max) {
            cout << e << " ";
        }

        //allocation
        cout << "     ";
        for (auto e : _allocation) {
            cout << e << " ";
        }

        //need
        cout << "     ";
        for (auto e : _need) {
            cout << e << " ";
        }
        cout << endl;
    }

    ~Process()
    { 
        _max.clear();
        _allocation.clear();
        _need.clear();
        _max.shrink_to_fit();
        _allocation.shrink_to_fit();
        _need.shrink_to_fit();
      //_request.clear();
    }
private:
    vector<int> _max;           //最大需求
    vector<int> _allocation;    //已分配的    
    vector<int> _need;          //尚需要的
 //   vector<int> _request;       //本次请求的   
};

//系统中的资源对象
//
//  每个对象是一个资源
//  对象中保存的是资源的sum和available
//
class Resources
{
public:
    
    Resources()
    {}
    
    //vector的大小应该与资源的总数有关
    void initValue(int resourcesnum)
    {
        _sum = resourcesnum;
    }

    //输入资源值
    void setValue()
    {
        cout << "请输入_sum：";
        cin >> _sum;
        cout << "请输入_available：";
        cin >> _available;
    }
        
    //获取资源总数
    int getSum()
    {
        return _sum;
    }

    //获取资源总数
    int getAvailable()
    {
        return _available;
    }

    //输出资源值
    void printValue()
    {
        cout << _sum << "        " << _available;
    }

    //析够函数
    ~Resources()
    {
        _sum = 0;
        _available = 0;
    }

private:
    int _sum;           //资源总数
    int _available;     //可利用的资源数目
};

//解决方案
//
//
//  负责初始化进程和资源
//  输入初始状态的 资源和进程
//  负责程序主体
//
//
class Solution
{
public:
    Solution()
        :_processnum(0)
         ,_resourcesnum(0)
    {}

    ~Solution()
    {
        _processnum = 0;
        _resourcesnum = 0;
        for (auto& e : _process) {
            e.~Process();
        }
        for (auto& e : _resources) {
            e.~Resources();
        }
        _process.clear();
        _process.shrink_to_fit();
        _resources.clear();
        _resources.shrink_to_fit();
    }


    //初始化各变量
    void initialize(int processnum = 0, int resourcesnum = 0)
    {
        //分别是进程数和资源类别数
        _processnum = processnum;
        _resourcesnum = resourcesnum;
        //提前预留空间
        _process.resize(processnum);
        _resources.resize(resourcesnum);
        for(int i = 0; i < processnum; ++i) {
            //为每一个进程将资源列表大小初始化好
            _process[i].initValue(resourcesnum);
        }
        for(int i = 0; i < resourcesnum; ++i) {
            //为每一个进程将资源列表大小初始化好
            _resources[i].initValue(resourcesnum);
        }
        
    }
    
    //输入资源的各项值
    void setResources()
    {
        cout << "开始输入资源信息：" << endl;
        for (auto& e : _resources)
            e.setValue();
    }


    //输入进程的各项属性
    void setProcess()
    {
        cout << "开始输入进程信息：" << endl;
        for (auto& e : _process) {
            e.setValue();
        }
    }

    //检测输入的有效性
    //即  进程的 max = need + allocation
    //    资源的 sum = available + allocation
    void checkValidity()
    {
        for (auto e : _process) {
        
        }
         

    }


    void printInfo()
    {
        //输出进程信息
        cout << "process:" << endl;
        cout << "max" << "          " << "allocation" << endl;
        for (auto e : _process) {
            e.printValue();
        }
        //输出资源信息
        cout << "resources:" << endl;
        cout << "sum" << "          " << "available" << endl;
        for (auto e : _resources) {
            e.printValue();
        }
    }

private:
    int _processnum;                   //进程数
    vector<Process> _process;           //用来存储进程
    int _resourcesnum;                //资源类型数
    vector<Resources> _resources;    //用来存储资源
};


#endif
