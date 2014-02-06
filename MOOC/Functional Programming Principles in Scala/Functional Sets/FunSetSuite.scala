package funsets

import org.scalatest.FunSuite
import org.junit.runner.RunWith
import org.scalatest.junit.JUnitRunner

@RunWith(classOf[JUnitRunner])
class FunSetSuite extends FunSuite {
    import FunSets._
    test("contains is implemented") {
        assert(contains(x => true, 100))
    }

    trait TestSets {
        val s1 = singletonSet(1)
        val s2 = singletonSet(2)
        val s3 = singletonSet(3)
    }

    test("singleton") {
        new TestSets {
            assert(contains(s1, 1), "Singleton")
        }
    }
  
    test("union") {
        new TestSets {
            val s = union(s1, s2)
            assert(contains(s, 1), "Union 1")
            assert(contains(s, 2), "Union 2")
            assert(!contains(s, 3), "Union 3")
        }
    }
  
    test("intersect") {
        new TestSets {
            val s4 = union(s1, s2);
            val s5 = union(s2, s3);
            val s = intersect(s4, s5);
            assert(!contains(s, 1), "Intersect 1")
            assert(contains(s, 2), "Intersect 2")
            assert(!contains(s, 3), "Intersect 3")
        }
    }
    
    test("diff") {
        new TestSets {
            val s4 = union(s1, s2);
            val s5 = union(s2, s3);
            val s = diff(s4, s5);
            assert(contains(s, 1), "Diff 1")
            assert(!contains(s, 2), "Diff 2")
            assert(!contains(s, 3), "Diff 3")
        }
    }
    
    test("filter") {
        new TestSets {
            val s = filter(union(s1, s2), x => x == 2)
            assert(!contains(s, 1), "Filter 1")
            assert(contains(s, 2), "Filter 2")
            assert(!contains(s, 3), "Filter 3")
        }
    }
    
    test("forall") {
        new TestSets {
            assert(forall(s2, x => x == 2), "Forall 1")
            assert(!forall(union(s1, s2), x => x == 2), "Forall 2")
        }
    }
    
    test("exist") {
        new TestSets {
            assert(!exists(s1, x => x == 2), "Exist 1")
            assert(exists(union(s1, s2), x => x == 2), "Exist 2")
        }
    }
    
    test("map") {
        new TestSets {
            val s = map(union(s1, s2), x => x * x)
            assert(contains(s, 1), "Map 1")
            assert(contains(s, 4), "Map 2")
            assert(!contains(s, 9), "Map 3")
        }
    }
}
