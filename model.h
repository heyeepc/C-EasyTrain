#ifndef TRAIN_MODEL_H
#define TRAIN_MODEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- 界面显示模板 ---
#define HEADER1 "------------ BOOK TICKET --------------\n"
#define HEADER2 "| number | start city | reach city | takeofftime | receivetime | price | ticketnumber |\n"
#define FORMAT  "|%-10s|%-10s|%-10s|%-10s|%-10s|%5d|  %5d   |\n"
#define DATA p->data.num, p->data.startcity, p->data.reachcity, p->data.takeofftime, p->data.receivetime, p->data.price, p->data.ticketnum

// --- 基础数据结构 ---
struct train {
    char num[10]; //列车号
    char startcity[10];  //出发城市
    char reachcity[10]; //目标城市
    char takeofftime[10]; //发车时间
    char receivetime[10];  //到达时间
    int price;  //票价
    int ticketnum;  //票数
};

struct man {
    char num[10]; //id
    char name[10];  //姓名
    int booknum;  // 订的票数
};

// --- 链表节点定义 ---
typedef struct train_node {
    struct train data;
    struct train_node *next;
} TrainNode, *TrainLink;

typedef struct man_node {
    struct man data;
    struct man_node *next;
} ManNode, *ManLink;

#endif

