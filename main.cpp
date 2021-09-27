#include <stdio.h>
#include <tchar.h>
#include <ostream>
#include <iostream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <fstream>

#define LENGTH 7
#define IN 3
#define OUT 4
using namespace std;
struct generator_way_point {
    int x;
    int y;
};
std::queue<generator_way_point> temp;
class Map {
public:
    int map[LENGTH][LENGTH] = { 0 };
    //    初始状态为全满
    struct generate_status {
        string direction = "";
        int counter = 0;
    };
    generate_status status;


    //    路径点结构体
    generator_way_point* generator_up_point(generator_way_point* now) {
        generator_way_point* p = (generator_way_point*)malloc(sizeof(generator_way_point));
        p->x = now->x;
        p->y = now->y - 1;
        map[p->x][p->y] = 1;
        return p;
    }//1
    generator_way_point* generator_down_point(generator_way_point* now) {
        generator_way_point* p = (generator_way_point*)malloc(sizeof(generator_way_point));
        p->x = now->x;
        p->y = now->y + 1;
        map[p->x][p->y] = 1;
        return p;
    }//2
    generator_way_point* generator_left_point(generator_way_point* now) {
        generator_way_point* p = (generator_way_point*)malloc(sizeof(generator_way_point));
        p->x = now->x - 1;
        p->y = now->y;
        map[p->x][p->y] = 1;
        return p;
    }//3
    generator_way_point* generator_right_point(generator_way_point* now) {
        generator_way_point* p = (generator_way_point*)malloc(sizeof(generator_way_point));
        p->x = now->x + 1;
        p->y = now->y;
        map[p->x][p->y] = 1;
        return p;
    }//4

    int judge_up(generator_way_point* now) {
        int x = now->x;
        int y = now->y;
        if (y == 0/*上边界*/ || map[x][y - 1] == 1/*回头路*/) { return 0; }
        else if ((x >= 1 && x <= LENGTH - 2)/*map[x-1][y]==0&&map[x+1][y]==*/
        && map[x - 1][y - 1] == 0 && map[x][y - 1] == 0 && map[x + 1][y - 1] == 0) {
            if (y == 1) {
                return 1;
            }
            else if (map[x][y - 2] == 0) {
                return 1;
            }
            else {
                return 0;
            }
        }
        else return 0;
    }
    int judge_down(generator_way_point* now) {
        int x = now->x;
        int y = now->y;
        if (y == LENGTH - 1/*边界*/ || map[x][y + 1] == 1/*回头路*/) { return 0; }
        else if ((x >= 1 && x <= LENGTH - 2)
        /*&&map[x-1][y]==0&&map[x+1][y]==0*/
        && map[x - 1][y + 1] == 0 && map[x][y + 1] == 0 && map[x + 1][y + 1] == 0) {
            if (y == LENGTH - 2) {
                return 1;
            }
            else if (map[x][y + 2] == 0) {
                return 1;
            }
            else {
                return 0;
            }
        }
        else return 0;
    }
    int judge_left(generator_way_point* now) {
        int x = now->x;
        int y = now->y;
        if (x == 0/*left边界*/ || map[x - 1][y] == 1/*回头路*/) { return 0; }
        else if ((y >= 1 && y <= LENGTH - 2)
        /*&&map[x][y-1]==0&&map[x][y+1]==0*/
        && map[x - 1][y + 1] == 0 && map[x - 1][y] == 0 && map[x - 1][y - 1] == 0) {
            if (x == 1) {
                return 1;
            }
            else if (map[x - 2][y] == 0) {
                return 1;
            }
            else {
                return 0;
            }
        }
        else return 0;
    }
    int judge_right(generator_way_point* now) {
        int x = now->x;
        int y = now->y;
        if (x == LENGTH - 1/*right边界*/ || map[x + 1][y] == 1/*回头路*/) { return 0; }
        else if ((y >= 1 && y <= LENGTH - 2)
        /*&&map[x][y-1]==0&&map[x][y+1]==0*/
        && map[x + 1][y + 1] == 0 && map[x + 1][y] == 0 && map[x + 1][y - 1] == 0) {
            if (x == LENGTH - 2) {
                return 1;
            }
            else if (map[x + 2][y] == 0) {
                return 1;
            }
            else {
                return 0;
            }
        }
        else return 0;
    }

    generator_way_point*
    rand_direction(int up = 0, int down = 0, int left = 0, int right = 0, generator_way_point* now = nullptr) {
        if (now) {
            int dire_value = up + down + left + right;
            srand((int)time(NULL));
            int one_way_max_length = rand() % 3 + 1;
            switch (dire_value) {
                case 0:
                    return nullptr;
                    case 1:
                        if (up == 1) {
                            status.counter++;
                            status.direction = "up";
                            return generator_up_point(now);
                        }
                        else if (down == 1) {
                            status.counter++;
                            status.direction = "down";
                            return generator_down_point(now);
                        }
                        else if (left == 1) {
                            status.counter++;
                            status.direction = "left";
                            return generator_left_point(now);
                        }
                        else if (right == 1) {
                            status.counter++;
                            status.direction = "right";
                            return generator_right_point(now);
                        }
                        break;
                        case 2:
                            if (up == 1 && down == 1) {
                                if (status.direction == "up" && status.counter < one_way_max_length) {
                                    status.counter++;
                                    return generator_up_point(now);
                                }
                                else {
                                    generator_way_point to_gen = { now->x,now->y - 1 };
                                    temp.push(to_gen);
                                    status.counter = 1;
                                    status.direction = "down";
                                    return generator_down_point(now);
                                }
                            }
                            else if (up == 1 && left == 1) {
                                if (status.direction == "up" && status.counter < one_way_max_length) {
                                    status.counter++;
                                    return generator_up_point(now);
                                }
                                else {
                                    generator_way_point to_gen = { now->x,now->y - 1 };
                                    temp.push(to_gen);
                                    status.counter = 1;
                                    status.direction = "left";
                                    return generator_left_point(now);
                                }
                            }
                            else if (down == 1 && left == 1) {
                                if (status.direction == "down" && status.counter < one_way_max_length) {
                                    status.counter++;
                                    return generator_down_point(now);
                                }
                                else {
                                    generator_way_point to_gen = { now->x,now->y + 1 };
                                    temp.push(to_gen);
                                    status.counter = 1;
                                    status.direction = "left";
                                    return generator_left_point(now);
                                }
                            }
                            else if (up == 1 && right == 1) {
                                if (status.direction == "up" && status.counter < one_way_max_length) {
                                    status.counter++;
                                    return generator_up_point(now);
                                }
                                else {
                                    generator_way_point to_gen = { now->x,now->y - 1 };
                                    temp.push(to_gen);
                                    status.counter = 1;
                                    status.direction = "right";
                                    return generator_right_point(now);
                                }
                            }
                            else if (down == 1 && right == 1) {
                                if (status.direction == "down" && status.counter < one_way_max_length) {
                                    status.counter++;
                                    return generator_down_point(now);
                                }
                                else {
                                    generator_way_point to_gen = { now->x,now->y + 1 };
                                    temp.push(to_gen);
                                    status.counter = 1;
                                    status.direction = "right";
                                    return generator_right_point(now);
                                }
                            }
                            else if (left == 1 && right == 1) {
                                if (status.direction == "left" && status.counter < one_way_max_length) {
                                    status.counter++;
                                    return generator_left_point(now);
                                }
                                else {
                                    generator_way_point to_gen = { now->x - 1,now->y };
                                    temp.push(to_gen);
                                    status.counter = 1;
                                    status.direction = "right";
                                    return generator_right_point(now);
                                }
                            }
                            break;
                            case 3:
                                if (up == 0) {
                                    if (status.direction == "left") {
                                        if (status.counter < one_way_max_length) {
                                            status.counter++;
                                            return generator_left_point(now);
                                        }
                                        else {
                                            generator_way_point to_gen = { now->x - 1,now->y };
                                            temp.push(to_gen);
                                            switch (((int)rand() % 2)) {
                                                case 0:
                                                    to_gen = { now->x + 1,now->y };
                                                    temp.push(to_gen);
                                                    status.counter = 1;
                                                    status.direction = "down";
                                                    return generator_down_point(now);
                                                    break;
                                                    case 1:
                                                        to_gen = { now->x,now->y + 1 };
                                                        temp.push(to_gen);
                                                        status.counter = 1;
                                                        status.direction = "right";
                                                        return generator_right_point(now);
                                                        break;
                                            }
                                        }
                                    }
                                    if (status.direction == "down") {
                                        if (status.counter < one_way_max_length) {
                                            status.counter++;
                                            return generator_down_point(now);
                                        }
                                        else {
                                            generator_way_point to_gen = { now->x,now->y + 1 };
                                            temp.push(to_gen);
                                            switch (((int)rand() % 2)) {
                                                case 0:
                                                    to_gen = { now->x + 1,now->y };
                                                    temp.push(to_gen);
                                                    status.counter = 1;
                                                    status.direction = "left";
                                                    return generator_left_point(now);
                                                    break;
                                                    case 1:
                                                        to_gen = { now->x - 1,now->y };
                                                        temp.push(to_gen);
                                                        status.counter = 1;
                                                        status.direction = "right";
                                                        return generator_right_point(now);
                                                        break;
                                            }
                                        }
                                    }
                                    if (status.direction == "right") {
                                        if (status.counter < one_way_max_length) {
                                            status.counter++;
                                            return generator_right_point(now);
                                        }
                                        else {
                                            generator_way_point to_gen = { now->x + 1,now->y };
                                            temp.push(to_gen);
                                            switch (((int)rand() % 2)) {
                                                case 0:
                                                    to_gen = { now->x,now->y + 1 };
                                                    temp.push(to_gen);
                                                    status.counter = 1;
                                                    status.direction = "left";
                                                    return generator_left_point(now);
                                                    break;
                                                    case 1:
                                                        to_gen = { now->x - 1,now->y };
                                                        temp.push(to_gen);
                                                        status.counter = 1;
                                                        status.direction = "down";
                                                        return generator_down_point(now);
                                                        break;
                                            }
                                        }
                                    }
                                }
                                else if (down == 0) {
                                    if (status.direction == "left") {
                                        if (status.counter < one_way_max_length) {
                                            status.counter++;
                                            return generator_left_point(now);
                                        }
                                        else {
                                            generator_way_point to_gen = { now->x - 1,now->y };
                                            temp.push(to_gen);
                                            switch (((int)rand() % 2)) {
                                                case 0:
                                                    to_gen = { now->x + 1,now->y };
                                                    temp.push(to_gen);
                                                    status.counter = 1;
                                                    status.direction = "up";
                                                    return generator_up_point(now);
                                                    break;
                                                    case 1:
                                                        to_gen = { now->x,now->y - 1 };
                                                        temp.push(to_gen);
                                                        status.counter = 1;
                                                        status.direction = "right";
                                                        return generator_right_point(now);
                                                        break;
                                            }
                                        }
                                    }
                                    if (status.direction == "up") {
                                        if (status.counter < one_way_max_length) {
                                            status.counter++;
                                            return generator_up_point(now);
                                        }
                                        else {
                                            generator_way_point to_gen = { now->x,now->y - 1 };
                                            temp.push(to_gen);
                                            switch (((int)rand() % 2)) {
                                                case 0:
                                                    to_gen = { now->x + 1,now->y };
                                                    temp.push(to_gen);
                                                    status.counter = 1;
                                                    status.direction = "left";
                                                    return generator_left_point(now);
                                                    break;
                                                    case 1:
                                                        to_gen = { now->x - 1,now->y };
                                                        temp.push(to_gen);
                                                        status.counter = 1;
                                                        status.direction = "right";
                                                        return generator_right_point(now);
                                                        break;
                                            }
                                        }
                                    }
                                    if (status.direction == "right") {
                                        if (status.counter < one_way_max_length) {
                                            status.counter++;
                                            return generator_right_point(now);
                                        }
                                        else {
                                            generator_way_point to_gen = { now->x + 1,now->y };
                                            temp.push(to_gen);
                                            switch (((int)rand() % 2)) {
                                                case 0:
                                                    to_gen = { now->x,now->y - 1 };
                                                    temp.push(to_gen);
                                                    status.counter = 1;
                                                    status.direction = "left";
                                                    return generator_left_point(now);
                                                    break;
                                                    case 1:
                                                        to_gen = { now->x - 1,now->y };
                                                        temp.push(to_gen);
                                                        status.counter = 1;
                                                        status.direction = "up";
                                                        return generator_up_point(now);
                                                        break;
                                            }
                                        }
                                    }
                                }
                                else if (left == 0) {
                                    if (status.direction == "down") {
                                        if (status.counter < one_way_max_length) {
                                            status.counter++;
                                            return generator_down_point(now);
                                        }
                                        else {
                                            generator_way_point to_gen = { now->x,now->y + 1 };
                                            temp.push(to_gen);
                                            switch (((int)rand() % 2)) {
                                                case 0:
                                                    to_gen = { now->x + 1,now->y };
                                                    temp.push(to_gen);
                                                    status.counter = 1;
                                                    status.direction = "up";
                                                    return generator_up_point(now);
                                                    break;
                                                    case 1:
                                                        to_gen = { now->x,now->y - 1 };
                                                        temp.push(to_gen);
                                                        status.counter = 1;
                                                        status.direction = "right";
                                                        return generator_right_point(now);
                                                        break;
                                            }
                                        }
                                    }
                                    if (status.direction == "up") {
                                        if (status.counter < one_way_max_length) {
                                            status.counter++;
                                            return generator_up_point(now);
                                        }
                                        else {
                                            generator_way_point to_gen = { now->x,now->y - 1 };
                                            temp.push(to_gen);
                                            switch (((int)rand() % 2)) {
                                                case 0:
                                                    to_gen = { now->x + 1,now->y };
                                                    temp.push(to_gen);
                                                    status.counter = 1;
                                                    status.direction = "down";
                                                    return generator_down_point(now);
                                                    break;
                                                    case 1:
                                                        to_gen = { now->x,now->y + 1 };
                                                        temp.push(to_gen);
                                                        status.counter = 1;
                                                        status.direction = "right";
                                                        return generator_right_point(now);
                                                        break;
                                            }
                                        }
                                    }
                                    if (status.direction == "right") {
                                        if (status.counter < one_way_max_length) {
                                            status.counter++;
                                            return generator_right_point(now);
                                        }
                                        else {
                                            generator_way_point to_gen = { now->x + 1,now->y };
                                            temp.push(to_gen);
                                            switch (((int)rand() % 2)) {
                                                case 0:
                                                    to_gen = { now->x,now->y + 1 };
                                                    temp.push(to_gen);
                                                    status.counter = 1;
                                                    status.direction = "up";
                                                    return generator_up_point(now);
                                                    break;
                                                    case 1:
                                                        to_gen = { now->x,now->y - 1 };
                                                        temp.push(to_gen);
                                                        status.counter = 1;
                                                        status.direction = "down";
                                                        return generator_down_point(now);
                                                        break;
                                            }
                                        }
                                    }
                                }
                                else if (right == 0) {
                                    if (status.direction == "left") {
                                        if (status.counter < one_way_max_length) {
                                            status.counter++;
                                            return generator_left_point(now);
                                        }
                                        else {
                                            generator_way_point to_gen = { now->x - 1,now->y };
                                            temp.push(to_gen);
                                            switch (((int)rand() % 2)) {
                                                case 0:
                                                    to_gen = { now->x,now->y + 1 };
                                                    temp.push(to_gen);
                                                    status.counter = 1;
                                                    status.direction = "up";
                                                    return generator_up_point(now);
                                                    break;
                                                    case 1:
                                                        to_gen = { now->x,now->y - 1 };
                                                        temp.push(to_gen);
                                                        status.counter = 1;
                                                        status.direction = "down";
                                                        return generator_down_point(now);
                                                        break;
                                            }
                                        }
                                    }
                                    if (status.direction == "up") {
                                        if (status.counter < one_way_max_length) {
                                            status.counter++;
                                            return generator_up_point(now);
                                        }
                                        else {
                                            generator_way_point to_gen = { now->x,now->y - 1 };
                                            temp.push(to_gen);
                                            switch (((int)rand() % 2)) {
                                                case 0:
                                                    to_gen = { now->x,now->y + 1 };
                                                    temp.push(to_gen);
                                                    status.counter = 1;
                                                    status.direction = "left";
                                                    return generator_left_point(now);
                                                    break;
                                                    case 1:
                                                        to_gen = { now->x - 1,now->y };
                                                        temp.push(to_gen);
                                                        status.counter = 1;
                                                        status.direction = "down";
                                                        return generator_down_point(now);
                                                        break;
                                            }
                                        }
                                    }
                                    if (status.direction == "down") {
                                        if (status.counter < one_way_max_length) {
                                            status.counter++;
                                            return generator_down_point(now);
                                        }
                                        else {
                                            generator_way_point to_gen = { now->x,now->y + 1 };
                                            temp.push(to_gen);
                                            switch (((int)rand() % 2)) {
                                                case 0:
                                                    to_gen = { now->x + 1,now->y };
                                                    temp.push(to_gen);
                                                    status.counter = 1;
                                                    status.direction = "left";
                                                    return generator_left_point(now);
                                                    break;
                                                    case 1:
                                                        to_gen = { now->x - 1,now->y };
                                                        temp.push(to_gen);
                                                        status.counter = 1;
                                                        status.direction = "right";
                                                        return generator_right_point(now);
                                                        break;
                                            }
                                        }
                                    }
                                }
                                break;
            }
        }
    }


    void generate_inner_way(void) {
        srand(time(0));
        generator_way_point start;
        start.x = 1 + (int)rand() % (LENGTH - 3);
        start.y = 0;
        temp.push(start);
        int counter = 0;
        while (!temp.empty()) {
            generator_way_point* temp_pt;
            temp_pt = &(temp.front());
            if (map[temp_pt->x][temp_pt->y] == 0 && temp_pt != nullptr) {
                int weight = judge_up(temp_pt) + judge_down(temp_pt)
                        + judge_left(temp_pt) + judge_right(temp_pt);

                if (weight >= 1 || counter == 0) {
                    map[temp_pt->x][temp_pt->y] = 1;
                    counter++;
                }
                else {
                    temp_pt = nullptr;
                }
            }
            while (temp_pt) {
                int up = judge_up(temp_pt);
                int down = judge_down(temp_pt);
                int left = judge_left(temp_pt);
                int right = judge_right(temp_pt);
                temp_pt = rand_direction(up, down, left, right, temp_pt);
                showmap();
            }
            //showmap();
            temp.pop();
        }
    }

    void generate(void) {
        generate_inner_way();
        int max_in = IN;
        int max_out = OUT;
        ofstream new_file("data.txt");
        for (int i = 0; i < LENGTH; i++) {
            if (i == 0) {
                new_file << " 0";
                for (int j = 0; j < LENGTH; ++j) {
                    if (map[j][i] == 1 &&
                    j > 0 && j < LENGTH - 2 && map[j - 1][i] != 1 && map[j + 1][i] != 1) {

                        new_file << " 2";

                    }
                    else {
                        new_file << " 0";
                    }
                }
                new_file <<  endl;
            }
            new_file << " 0";
            for (int j = 0; j < LENGTH; j++) {
                if (j == 0 || j == LENGTH - 1) {
                    new_file << " 0";
                }
                else {
                    new_file << " " << map[j][i];
                }
            }
            new_file << endl;
            if (i == LENGTH - 1) {
                new_file << " 0";
                for (int j = 0; j < LENGTH; ++j) {
                    if (map[j][i] == 1 &&
                    j > 0 && j < LENGTH - 2 && map[j - 1][i] != 1 && map[j + 1][i] != 1) {

                        new_file << " 1";

                    }
                    else {
                        new_file << " 0";
                    }
                }
                new_file <<  endl;
            }
        }
    }

    void showmap() {
        system("cls");
        for (int i = 0; i < LENGTH; i++) {
            for (int j = 0; j < LENGTH; j++) {
                printf("%d", map[j][i]);
            }
            printf("\n");
        }
        printf("\n");
        printf("\n");
        printf("\n");
        //system("pause");
        return;
    }
};


int main() {
    Map map;
    map.generate();
}

/*
 *


 *
 * */