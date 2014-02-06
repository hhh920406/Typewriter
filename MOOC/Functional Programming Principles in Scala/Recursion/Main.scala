package recfun
import common._

object Main {
    def main(args: Array[String]) {
        println("Pascal's Triangle")
        for (row <- 0 to 10) {
            for (col <- 0 to row)
                print(pascal(col, row) + " ")
            println()
        }
    }

    def pascal(c: Int, r: Int): Int = {
        if (c == 0 || c == r) {
            1
        } else {
            pascal(c, r - 1) + pascal(c - 1, r - 1)
        }
    }

  def balance(chars: List[Char]): Boolean = {
      def matches(depth : Int, str: List[Char]) : Boolean = {
          if (str.isEmpty) {
              depth == 0
          } else if (depth < 0) {
              false
          } else if (str.head == '(') {
              matches(depth + 1, str.tail)
          } else if (str.head == ')') {
              matches(depth - 1, str.tail)
          } else {
              matches(depth, str.tail)
          }
       }
       matches(0, chars)
    }

    def countChange(money: Int, coins: List[Int]): Int = {
        if (money == 0) {
            1
        } else if (money < 0 || coins.isEmpty) {
            0
        } else {
            countChange(money, coins.tail) + countChange(money - coins.head, coins)
        }
    }
}
