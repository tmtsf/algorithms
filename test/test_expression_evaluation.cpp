#include "gtest/gtest.h"
#include "stack.hpp"

namespace cheetah
{
  namespace test
  {
    TEST(test_expression_evaluation, Evaluation)
    {
      const std::string expr("( 1 + ( (2.4 + 3) * (4 * 5) ) )");

      cheetah::stack<char> ops;
      cheetah::stack<double> vals;

      for (int i=0; i<expr.size(); ++i)
      {
        char c = expr[i];
        switch (c)
        {
          case ' ':
          case '(':
            break;
          case '+':
          case '-':
          case '*':
          case '/':
            ops.push(c);
            break;
          case ')':
          {
            char op = ops.top();
            ops.pop();

            double v1 = vals.top();
            vals.pop();
            double v2 = vals.top();
            vals.pop();

            double v;
            switch (op)
            {
              case '+':
                v = v1 + v2;
                break;
              case '-':
                v = v1 - v2;
                break;
              case '*':
                v = v1 * v2;
                break;
              case '/':
                v = v1 / v2;
                break;
              default:
                std::cout << "Cannot understand the operator!\n";
                exit(1);
                break;
            }

            vals.push(v);
            break;
          }
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':
          case '0':
          case '.':
          {
            int temp = i;
            do
            {
              ++i;
            } while (isdigit(expr[i]) || expr[i] == '.');

            double v = std::stod(expr.substr(temp, i-temp));
            vals.push(v);
            --i;
            break;
          }
          default:
            std::cout << "Invalid expression!\n";
            exit(1);
            break;
        }
      }

      std::cout << vals.top() << "\n";
      vals.pop();

      assert(vals.empty());
      assert(ops.empty());
    }
  }
}
