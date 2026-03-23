
#ifndef TRAIN_MODEL_H
#define TRAIN_MODEL_H

// --- 界面显示模板 ---
#define HEADER1 "------------ BOOK TICKET --------------\n"
#define HEADER2 "| number | start city | reach city | takeofftime | receivetime | price | ticketnumber |\n"
#define FORMAT  "|%-10s|%-10s|%-10s|%-10s|%-10s|%5d|  %5d   |\n"
// 注意：DATA 宏通常配合链表指针 p 使用，确保你使用它时，当前函数里确实有名为 p 的指针
#define DATA p->data.num, p->data.startcity, p->data.reachcity, p->data.takeofftime, p->data.receivetime, p->data.price, p->data.ticketnum

// --- 结构体定义 ---
// 这里接着写书上的 struct Train {...} 等内容


#endif
