#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

vector <string>
ParseIntoStrings(string a)
{
    string rhs = a;
    vector <string> Result;
    for (int i = 0; i < a.length(); i++)
    {
        string delim = " ";
        int pos = rhs.find(delim);
        string lhs;
        if (pos != string::npos)
        {
            lhs = rhs.substr(0,pos);
            Result.push_back(lhs);
            rhs = rhs.substr(pos+delim.length(), a.length()-1);
        }
        
        if (pos == string::npos)
        {
            Result.push_back(rhs);
        }
        
    }
    return Result;
}

vector <int>
ParseIntoInt(string a)
{
    string rhs = a;
    vector <int> Result;
    int pos;
    while(pos != -1)
    {
        string delim = " ";
        pos = rhs.find(delim);
        string lhs;
        if (pos != string::npos)
        {
            lhs = rhs.substr(0,pos);
            Result.push_back(stoi(lhs));
            rhs = rhs.substr(pos+delim.length(), a.length()-1);
        }
        
        if (pos == string::npos)
        {
            Result.push_back(stoi(rhs));
        }
        
    }
    return Result;    
}

int
main()
{
    string a ="0 71 97 97 99 99 99 113 113 114 114 114 115 128 128 128 131 137 147 147 147 163 184 184 186 196 210 213 225 225 228 230 236 242 242 246 246 260 262 268 275 277 281 297 301 310 314 324 331 333 338 339 341 344 356 361 367 367 388 389 391 393 394 409 409 411 424 429 438 444 448 453 459 461 464 466 472 481 488 502 508 519 523 524 526 538 541 547 552 556 563 572 573 575 576 580 592 595 601 609 616 619 637 639 666 669 669 670 671 672 673 675 677 686 689 691 694 706 708 708 710 715 732 756 763 765 772 783 784 785 785 786 797 803 805 805 805 820 822 823 852 855 855 857 857 862 862 869 882 885 899 911 912 916 919 919 919 933 940 952 956 961 968 970 970 971 983 983 985 999 1009 1010 1013 1027 1032 1033 1039 1047 1053 1065 1069 1080 1082 1082 1085 1097 1098 1098 1099 1103 1108 1117 1124 1130 1136 1141 1150 1152 1161 1193 1194 1195 1196 1196 1196 1212 1213 1213 1216 1216 1223 1229 1229 1245 1245 1249 1249 1264 1266 1278 1307 1308 1309 1310 1310 1311 1324 1327 1328 1341 1343 1344 1346 1359 1360 1363 1376 1377 1377 1378 1379 1380 1409 1421 1423 1438 1438 1442 1442 1458 1458 1464 1471 1471 1474 1474 1475 1491 1491 1491 1492 1493 1494 1526 1535 1537 1546 1551 1557 1563 1570 1579 1584 1588 1589 1589 1590 1602 1605 1605 1607 1618 1622 1634 1640 1648 1654 1655 1660 1674 1677 1678 1688 1702 1704 1704 1716 1717 1717 1719 1726 1731 1735 1747 1754 1768 1768 1768 1771 1775 1776 1788 1802 1805 1818 1825 1825 1830 1830 1832 1832 1835 1864 1865 1867 1882 1882 1882 1884 1890 1901 1902 1902 1903 1904 1915 1922 1924 1931 1955 1972 1977 1979 1979 1981 1993 1996 1998 2001 2010 2012 2014 2015 2016 2017 2018 2018 2021 2048 2050 2068 2071 2078 2086 2092 2095 2107 2111 2112 2114 2115 2124 2131 2135 2140 2146 2149 2161 2163 2164 2165 2168 2179 2185 2199 2206 2215 2221 2223 2226 2228 2234 2239 2243 2249 2258 2263 2276 2278 2278 2293 2294 2296 2298 2299 2320 2320 2326 2331 2343 2346 2348 2349 2354 2356 2363 2373 2377 2386 2390 2406 2410 2412 2419 2425 2427 2441 2441 2445 2445 2451 2457 2459 2462 2462 2474 2477 2491 2501 2503 2503 2524 2540 2540 2540 2550 2556 2559 2559 2559 2572 2573 2573 2573 2574 2574 2588 2588 2588 2590 2590 2616 2687";
    vector <int> aa = ParseIntoInt(a);
    for (int i = 0; i < aa.size()-1; i++)
    {
        cout << aa[i]<<',';
    }
    cout << aa[aa.size()-1];
    
}