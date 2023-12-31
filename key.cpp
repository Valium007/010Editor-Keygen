#include <gmpxx.h>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

int raw[1000] = {
    969622712,  594890599,  1593930257, 1052452058, 890701766,  1677293387,
    394424968,  266815521,  1532978959, 1211194088, 2019260265, 729421127,
    953225874,  1117854514, 892543556,  2000911200, 514538256,  1400963072,
    486675118,  1862498216, 1136668818, 758909582,  1653935295, 821063674,
    888606944,  687085563,  890056597,  1513495898, 365692427,  184357836,
    677395407,  863045227,  818746596,  391985767,  1842768403, 758385145,
    1478392706, 1985112985, 1552765320, 746944881,  368385984,  1758203153,
    1240817244, 660489060,  756944316,  1290697955, 844453952,  288239112,
    1769473626, 1922176006, 826636519,  391520695,  1081548223, 1069693142,
    1244729994, 766313326,  1101031894, 624951698,  14501479,   1794907983,
    1460682958, 1660839647, 1104890686, 897721119,  1442187162, 480708164,
    454443986,  1064446153, 1595150448, 1041527979, 1145775470, 1399869657,
    255985995,  802693350,  2005610078, 1897360642, 2146073193, 1538606632,
    431647857,  964049561,  395138253,  19164808,   856904574,  730737943,
    708645054,  1506870658, 933323739,  819349658,  1780571206, 236747382,
    533160167,  2042104933, 670325172,  2040165158, 1354372994, 705785180,
    1669754395, 1066536508, 1426207888, 1437950089, 741941201,  796931522,
    1694313338, 1290302874, 1367672048, 2039808424, 1062939821, 954597728,
    1668694488, 859122242,  1369582617, 140269649,  53024683,   729221831,
    816609203,  736893191,  55706320,   262747091,  1629838835, 581764799,
    1488480625, 1607077349, 1879925846, 1453945819, 1521965565, 856558562,
    1530662365, 1230847072, 1404918182, 1281256849, 1238970765, 272453753,
    1640907491, 2127893021, 350314733,  556617458,  654390256,  1648581270,
    531062411,  1862873022, 1241517385, 1471028336, 5121143,    1444839026,
    1183580211, 1573659650, 2018540230, 1487873223, 234237236,  898254600,
    1023090193, 728843548,  2007454357, 1451820833, 267351539,  302982385,
    26807015,   865879122,  664886158,  195503981,  1625037691, 1330347906,
    1742434311, 1330272217, 1645368040, 542321916,  1782121222, 411042851,
    435386250,  1176704752, 1454246199, 1136813916, 1707755005, 224415730,
    201138891,  989750331,  1006010278, 1147286905, 406860280,  840388503,
    1282017578, 1605698145, 23396724,   862145265,  1898780916, 1855549801,
    1571519230, 2083204840, 1859876276, 1602449334, 1009413590, 690816450,
    86131931,   345661263,  1565025600, 857544170,  1329948960, 1211787679,
    994381573,  991984748,  1956475134, 1098146294, 1655714289, 659576699,
    689116467,  1485584392, 451884118,  255590636,  2108114754, 1266252396,
    1589326471, 2019907768, 15552498,   1651075358, 614606175,  1656823678,
    797605325,  1681594366, 2005080248, 624648446,  884695971,  1526931791,
    1595240948, 439447199,  2060396292, 680093752,  409028215,  469068267,
    195583689,  1791650630, 507724330,  1364025102, 1094582668, 813049577,
    32316922,   1240756058, 1176200235, 2104494066, 325396055,  1796606917,
    1709197385, 525495836,  1510101430, 735526761,  767523533,  1374043776,
    1559389967, 567085571,  1560216161, 867042846,  1001796703, 1568754293,
    628841972,  173812827,  379868455,  384973125};

mpz_t a, v;

void encode_nm(std::string &name, int l, int u) {

  mpz_init(a);
  mpz_set_ui(a, 0);
  int n = name.length();
  int x = 0;
  l = l * 17, u = u * 15;

  for (int i = 0; i < n; i++) {
    int c = (int)std::toupper(name[i]);
    mpz_t p, q;
    mpz_init(p);
    mpz_init(q);

    mpz_set_ui(p, raw[c + 13 & 0xff]);
    mpz_set_ui(q, raw[c + 0x2f & 0xff]);

    mpz_add_ui(a, a, raw[c]);
    mpz_xor(a, a, p);
    mpz_mul(a, a, q);
    mpz_add_ui(a, a, raw[x & 0xff]);
    mpz_add_ui(a, a, raw[l & 0xff]);
    mpz_add_ui(a, a, raw[u & 0xff]);
    x += 19;
    l += 9;
    u += 13;
  }
}

int encode_users(int num) { return (num * 11 ^ 0x3421) - 0x4d30 ^ 0x7892; }

int encode_pd(int a, int b) {
  return (a * 17 ^ 0xa8e53167) + 0x2c175 ^ 0xff22c078 ^ b;
}

void fl(int unsigned long p[]) {
  int s = 0;
  for (int i = 0; i < 10; i += 2) {
    int t = p[i] << 8 | p[i + 1];
    s += 1;
    if (s == 5) {
      printf("%04X\n", (t & 0xffff));
    } else {
      printf("%04X-", (t & 0xffff));
    }
  }
}

int rshift(mpz_t rop, int bits) {
  mpz_t i;
  mpz_init(i);
  mpz_fdiv_q_2exp(i, rop, bits);
  return mpz_get_ui(i);
}

int _end(mpz_t op1, mpz_t op2) {
  mpz_t rop;
  mpz_init(rop);
  mpz_and(rop, op1, op2);
  return mpz_get_ui(rop);
}

void gl(std::string &name, int users, int days_left) {
  mpz_init(v);
  mpz_set_ui(v, 255);
  int unsigned long p[10] = {0};
  p[3] = 0xac;
  days_left += 0x4596 + 83;
  encode_nm(name, days_left, users);
  p[4] = _end(a, v);
  p[5] = rshift(a, 8) & 0xff;
  p[6] = rshift(a, 16) & 0xff;
  p[7] = rshift(a, 24) & 0xff;
  int encoded_date = encode_pd(days_left, 0x5b8c27);
  int enc_users = encode_users(users);
  p[2] = p[5] ^ (enc_users & 0xff);
  p[1] = p[7] ^ (enc_users >> 8 & 0xff);
  p[0] = p[6] ^ (encoded_date & 0xff);
  p[8] = p[4] ^ (encoded_date >> 8 & 0xff);
  p[9] = p[5] ^ (encoded_date >> 16 & 0xff);
  fl(p);
}

int getIntInput(const std::string &msg, int from, int to) {

  std::string input;
  bool isValidInput = false;
  int validinput;

  while (!isValidInput) {
    try {
      std::cout << msg << from << " and " << to << ":\t";
      std::cin >> input;

      size_t takenChars;
      validinput = std::stoi(input, &takenChars);
      if (validinput >= from && validinput <= to && takenChars == input.size())
        isValidInput = true;
    } catch (...) {
    }
  }

  return validinput;
}

int main() {

  std::string name;
  std::cout << "Enter name: ";
  std::cin >> name;
  std::string usg = "Enter users between ";
  std::string dsg = "Enter days between ";
  gl(name, getIntInput(usg, 1, 9999), getIntInput(dsg, 1, 9999));
}
