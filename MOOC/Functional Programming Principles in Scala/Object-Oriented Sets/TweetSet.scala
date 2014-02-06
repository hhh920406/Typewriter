package objsets

import common._
import TweetReader._

class Tweet(val user: String, val text: String, val retweets: Int) {
    override def toString: String = 
        "User: " + user + "\n" +
        "Text: " + text + "[" + retweets + "]"
}
import scala.io.Source
abstract class TweetSet {
    def filter(p: Tweet => Boolean): TweetSet = filterAcc(p, new Empty())
    def filterAcc(p: Tweet => Boolean, acc: TweetSet): TweetSet
    def union(that: TweetSet): TweetSet
    def mostRetweeted: Tweet = findMax
    def descendingByRetweet: TweetList = {
        def descending(s: TweetSet): TweetList = {
            if (s.isEmpty) {
                Nil
            } else {
                val head = s.mostRetweeted
                new Cons(head, descending(s.remove(head)))
            }
        }
        descending(this)
    }
    def findMax(): Tweet
    def isEmpty: Boolean;
    def incl(tweet: Tweet): TweetSet
    def remove(tweet: Tweet): TweetSet
    def contains(tweet: Tweet): Boolean
    def foreach(f: Tweet => Unit): Unit
}

class Empty extends TweetSet {
    override def toString = "."
    def isEmpty = true
    def findMax() : Tweet = {
        new Tweet("", "", -1);
    }
    def filterAcc(p: Tweet => Boolean, acc: TweetSet): TweetSet = acc
    def union(that: TweetSet): TweetSet = that
    def contains(tweet: Tweet): Boolean = false
    def incl(tweet: Tweet): TweetSet = new NonEmpty(tweet, new Empty, new Empty)
    def remove(tweet: Tweet): TweetSet = this
    def foreach(f: Tweet => Unit): Unit = ()
}

class NonEmpty(elem: Tweet, left: TweetSet, right: TweetSet) extends TweetSet {
    override def toString = "{" + left + elem + right + "}"
    
    def isEmpty = false
    
    def findMax(): Tweet = {
        def max(a: Tweet, b: Tweet): Tweet = if (a.retweets > b.retweets) a else b
        if (left.isEmpty && right.isEmpty) elem
        else if (!left.isEmpty && right.isEmpty) max(elem, left.findMax())
        else if (left.isEmpty && !right.isEmpty) max(elem, right.findMax())
        else max(elem, max(left.findMax(), right.findMax()))
    }
    
    def filterAcc(p: Tweet => Boolean, acc: TweetSet): TweetSet = {
        if (p(elem)) left.filterAcc(p, right.filterAcc(p, acc.incl(elem)))
        else left.filterAcc(p, right.filterAcc(p, acc))
    }
    
    def union(that: TweetSet): TweetSet = this.filterAcc(tweet => true, that)

    def contains(x: Tweet): Boolean =
        if (x.text < elem.text) left.contains(x)
        else if (elem.text < x.text) right.contains(x)
        else true

    def incl(x: Tweet): TweetSet = {
        if (x.text < elem.text) new NonEmpty(elem, left.incl(x), right)
        else if (elem.text < x.text) new NonEmpty(elem, left, right.incl(x))
        else this
    }

    def remove(tw: Tweet): TweetSet =
        if (tw.text < elem.text) new NonEmpty(elem, left.remove(tw), right)
        else if (elem.text < tw.text) new NonEmpty(elem, left, right.remove(tw))
        else left.union(right)

    def foreach(f: Tweet => Unit): Unit = {
        f(elem)
        left.foreach(f)
        right.foreach(f)
    }
}

trait TweetList {
    def head: Tweet
    def tail: TweetList
    def isEmpty: Boolean
    def foreach(f: Tweet => Unit): Unit =
        if (!isEmpty) {
            f(head)
            tail.foreach(f)
    }
}

object Nil extends TweetList {
    def head = throw new java.util.NoSuchElementException("head of EmptyList")
    def tail = throw new java.util.NoSuchElementException("tail of EmptyList")
    def isEmpty = true
}

class Cons(val head: Tweet, val tail: TweetList) extends TweetList {
    def isEmpty = false
}

object GoogleVsApple {
    val google = List("android", "Android", "galaxy", "Galaxy", "nexus", "Nexus")
    val apple = List("ios", "iOS", "iphone", "iPhone", "ipad", "iPad")

    lazy val googleTweets: TweetSet = TweetReader.allTweets.filter(p => google.exists(s => p.text.contains(s)))
    lazy val appleTweets: TweetSet = TweetReader.allTweets.filter(p => apple.exists(s => p.text.contains(s)))

    lazy val trending: TweetList = googleTweets.union(appleTweets).descendingByRetweet
}

object Main extends App {
    GoogleVsApple.trending foreach println
}
