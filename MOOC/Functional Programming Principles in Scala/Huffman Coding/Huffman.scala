package patmat

import common._

object Huffman {
    abstract class CodeTree
    case class Fork(left: CodeTree, right: CodeTree, chars: List[Char], weight: Int) extends CodeTree
    case class Leaf(char: Char, weight: Int) extends CodeTree

    def weight(tree: CodeTree): Int = tree match {
        case Fork(left, right, chars, weight) => weight
        case Leaf(char, weight) => weight
    }

    def chars(tree: CodeTree): List[Char] = tree match {
        case Fork(left, right, chars, weight) => chars
        case Leaf(char, weight) => List(char)
    }

    def makeCodeTree(left: CodeTree, right: CodeTree) =
        Fork(left, right, chars(left) ::: chars(right), weight(left) + weight(right))

    def string2Chars(str: String): List[Char] = str.toList

    def times(chars: List[Char]): List[(Char, Int)] = {
        def dfs(charList: List[Char], list: List[(Char, Int)]): List[(Char, Int)] = charList match {
            case Nil => list
            case head :: tail => dfs(tail.filter(_ != head), (head, chars.count(_ == head)) :: list)
        }
        dfs(chars, List())
    }

    def makeOrderedLeafList(freqs: List[(Char, Int)]): List[Leaf] = {
        freqs.sortBy(_._2).map(v => Leaf(v._1, v._2))
    }

    def singleton(trees: List[CodeTree]): Boolean = trees.size == 1

    def combine(trees: List[CodeTree]): List[CodeTree] = {
        if (trees.size <= 1) {
            trees
        } else {
            (makeCodeTree(trees(0), trees(1)) :: trees.drop(2)).sortBy(weight(_))
        }
    }
    
    def until(singleton: List[CodeTree] => Boolean, combine: List[CodeTree] => List[CodeTree])(trees: List[CodeTree]): CodeTree = {
        if (singleton(trees)) {
            trees.head
        } else {
            until(singleton, combine)(combine(trees))
        }
    }

    def createCodeTree(chars: List[Char]): CodeTree = {
        until(singleton, combine)(makeOrderedLeafList(times(chars)))
    }

    type Bit = Int
    
    def decode(tree: CodeTree, bits: List[Bit]): List[Char] = {
        def dfs(root: CodeTree, bitList: List[Bit], acc: List[Char]): List[Char] = bitList match {
            case Nil => root match {
                case Fork(left, right, chars, weight) => throw new Exception()
                case Leaf(char, weight) => acc :+ char
            }
            case head :: tail => root match {
                case Fork(left, right, chars, weight) => dfs(if (head == 0) left else right, tail, acc)
                case Leaf(char, weight) => dfs(tree, bitList, acc :+ char)
            }
        }
        dfs(tree, bits, List())
    }

    val frenchCode: CodeTree = Fork(Fork(Fork(Leaf('s',121895),Fork(Leaf('d',56269),Fork(Fork(Fork(Leaf('x',5928),Leaf('j',8351),List('x','j'),14279),Leaf('f',16351),List('x','j','f'),30630),Fork(Fork(Fork(Fork(Leaf('z',2093),Fork(Leaf('k',745),Leaf('w',1747),List('k','w'),2492),List('z','k','w'),4585),Leaf('y',4725),List('z','k','w','y'),9310),Leaf('h',11298),List('z','k','w','y','h'),20608),Leaf('q',20889),List('z','k','w','y','h','q'),41497),List('x','j','f','z','k','w','y','h','q'),72127),List('d','x','j','f','z','k','w','y','h','q'),128396),List('s','d','x','j','f','z','k','w','y','h','q'),250291),Fork(Fork(Leaf('o',82762),Leaf('l',83668),List('o','l'),166430),Fork(Fork(Leaf('m',45521),Leaf('p',46335),List('m','p'),91856),Leaf('u',96785),List('m','p','u'),188641),List('o','l','m','p','u'),355071),List('s','d','x','j','f','z','k','w','y','h','q','o','l','m','p','u'),605362),Fork(Fork(Fork(Leaf('r',100500),Fork(Leaf('c',50003),Fork(Leaf('v',24975),Fork(Leaf('g',13288),Leaf('b',13822),List('g','b'),27110),List('v','g','b'),52085),List('c','v','g','b'),102088),List('r','c','v','g','b'),202588),Fork(Leaf('n',108812),Leaf('t',111103),List('n','t'),219915),List('r','c','v','g','b','n','t'),422503),Fork(Leaf('e',225947),Fork(Leaf('i',115465),Leaf('a',117110),List('i','a'),232575),List('e','i','a'),458522),List('r','c','v','g','b','n','t','e','i','a'),881025),List('s','d','x','j','f','z','k','w','y','h','q','o','l','m','p','u','r','c','v','g','b','n','t','e','i','a'),1486387)
    val secret: List[Bit] = List(0,0,1,1,1,0,1,0,1,1,1,0,0,1,1,0,1,0,0,1,1,0,1,0,1,1,0,0,1,1,1,1,1,0,1,0,1,1,0,0,0,0,1,0,1,1,1,0,0,1,0,0,1,0,0,0,1,0,0,0,1,0,1)
    def decodedSecret: List[Char] = decode(frenchCode, secret)

    def encode(tree: CodeTree)(text: List[Char]): List[Bit] = {
        def dfs(root: CodeTree, textList: List[Char], acc: List[Bit]) : List[Bit] = textList match {
            case Nil => acc
            case head :: tail => root match {
                case Fork(left, right, charss, weight) => {
                    if (chars(left).contains(head)) dfs(left, textList, acc :+ 0)
                    else if (chars(right).contains(head)) dfs(right, textList, acc :+ 1)
                    else throw new Exception()
                }
                case Leaf(char, weight) => dfs(tree, tail, acc)
            }
        }
        dfs(tree, text, List())
    }

    type CodeTable = List[(Char, List[Bit])]
    def codeBits(table: CodeTable)(char: Char): List[Bit] = table match {
        case Nil => List()
        case (c, list) :: tail => {
            if (c == char) list
            else codeBits(tail)(char)
        }
    }

    def convert(tree: CodeTree): CodeTable = {
        def dfs(root: CodeTree, acc: List[Bit]): CodeTable = root match {
            case Fork(left, right, chars, weight) => dfs(left, acc :+ 0) ::: dfs(right, acc :+ 1)
            case Leaf(char, weight) => List((char, acc))
        }
        dfs(tree, List())
    }

    def mergeCodeTables(a: CodeTable, b: CodeTable): CodeTable = a ::: b

    def quickEncode(tree: CodeTree)(text: List[Char]): List[Bit] = {
        val table = convert(tree)
        def dfs(textList: List[Char], acc: List[Bit]) : List[Bit] = textList match {
            case Nil => acc
            case head :: tail => dfs(tail, acc ::: codeBits(table)(head))
        }
        dfs(text, List())
    }
}
