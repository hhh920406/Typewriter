package example

import common._

object Lists {
    def sum(xs: List[Int]): Int = {
        if (xs.isEmpty) {
            0
        } else {
            xs.head + sum(xs.tail)
        }
    }
  
    def max(xs: List[Int]): Int = {
        if (xs.isEmpty) {
            throw new java.util.NoSuchElementException()
        } else {
            if (xs.tail.isEmpty) {
                xs.head
            } else {
	            def m : Int = max(xs.tail)
	            if (xs.head > m) {
	            xs.head
	        } else {
		        m
	        }
          }
        }
    }
}
