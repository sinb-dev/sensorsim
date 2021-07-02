#include <iostream>
#include <fstream>

using namespace std;

int main()
{
  ifstream in("raw.txt");
  ofstream out("src/random_raw/random_raw.c");

  size_t count = 0;
  string str;

  out << "#ifndef RANDOM_RAW_C\n";
  out << "#define RANDOM_RAW_C\n\n";
  out << "// This file is generated - do not edit\n\n";
  out << "unsigned char random_data[] = {";
  while (in >> str)
  {
    if (count != 0) out << ", ";
    if (count % 12 == 0) out << "\n";
    out << "0x" << str;

    count++;
  }
  out << "};\n\n";
  out << "#define RANDOM_DATA_SIZE " << count << "\n\n";
  out << "#endif";

  return 0;
}
