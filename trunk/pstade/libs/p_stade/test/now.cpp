
#include <pstade/vodka/drink.hpp>
#include <pstade/biscuit.hpp>
#include <pstade/oven/sequence_cast.hpp>

#include <sstream>
//#include <boost/test/unit_test.hpp>
//#include <boost/test/minimal.hpp>
//#include <boost/range.hpp>
#include <boost/lexical_cast.hpp>

#include <string>
#include <iostream>
//#include <boost/regex.hpp>


using namespace std;
using namespace pstade;
using namespace biscuit;


const wstring wtext(L"��/�� Hello, ���񂾂� Biscuit! >");
const string text("</�� Hello, ���񂾂� Biscuit! >");

//string ww( caps[0].begin(), caps[0].end()); // iterator_range �� string �s 
//cout << ww<<endl;
//wstring www( wcaps[0].begin(), wcaps[0].end());
//wcout << www <<endl;

#include <pstade/biscuit/parser/utility/symbol.hpp>
PSTADE_BISCUIT_SYMBOL(hello, "hello")
PSTADE_BISCUIT_SYMBOL(bye, "bye")
PSTADE_BISCUIT_SYMBOL(wbye, L"��������bye")
struct ff : debugger<ff,
     	bye
> { };

int wmain()
{
  locale::global(locale("japanese"));// windows ���{�� �O��S-JIS ����wchar_t

  //biscuit::debugger_reset_ostream(std::cout);

//wcout << biscuit::match<hello>("hello") ;
//wcout << biscuit::match<bye>("bye") ;
  wcout  << biscuit::match<ff>(std::string("bye")) ;// debugger �� wchar_t ���Ή�
//  struct ff: "2845023383123631239498121101"     �\�i���ł� ��  ��
//  /struct ff: ""
//  1      �������� �p�[�X�͐���炵��

//
//cout << oven::sequence_cast<string>(rng); // range �� string �s��
//wcout << biscuit::search<bye>(L"--bye") ;


   return 0;
}