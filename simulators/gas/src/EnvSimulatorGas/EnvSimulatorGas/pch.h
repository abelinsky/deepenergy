// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.

#ifndef PCH_H
#define PCH_H

// TODO: add headers that you want to pre-compile here
#define NOMINMAX
#include <windows.h>
#undef NOMINMAX

#include <string>
#include <stdio.h>
#include <iostream>
#include <thread>
#include <fstream>
#include <stdarg.h>

#include <algorithm>
#include <cmath>

#include <map>
#include <deque>
#include <vector>
#include <list>
#include <set>

#include <unordered_map>
#include <unordered_set>

#include <cassert>

#include <experimental/filesystem>

using namespace std;
using namespace stdext;

#include <boost/bind.hpp>
#include <boost/format.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
using namespace boost;

namespace fs = std::experimental::filesystem;

#include "Core/OptDefines.h"
#include "Core/GlobalData.h"
#include "utils.h"

#endif //PCH_H
