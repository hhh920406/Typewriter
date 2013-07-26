package forcomp

import common._

object Anagrams {
    type Word = String
    type Sentence = List[Word]
    type Occurrences = List[(Char, Int)]
    val dictionary: List[Word] = loadDictionary
    
    def wordOccurrences(w: Word): Occurrences =  w.toLowerCase().groupBy(x => x).map(x => (x._1, x._2.size)).toList.sortBy(_._1)
    def sentenceOccurrences(s: Sentence): Occurrences = wordOccurrences(s.foldLeft("")(_ + _))
    lazy val dictionaryByOccurrences: Map[Occurrences, List[Word]] = dictionary.groupBy(wordOccurrences(_)).withDefaultValue(List())
    def wordAnagrams(word: Word): List[Word] = dictionaryByOccurrences(wordOccurrences(word))
    
    def combinations(occurrences: Occurrences): List[Occurrences] = occurrences match {
        case Nil => List(List())
        case head :: tail => for {
            current <- (0 to head._2).map((head._1, _)).toList
            combine <- combinations(tail)
        } yield if (current._2 == 0) combine else current :: combine
    }

    def subtract(x: Occurrences, y: Occurrences): Occurrences = {
        x.foldLeft(List[(Char, Int)]())((a: List[(Char, Int)], b : (Char, Int)) => {
            y.filter(_._1 == b._1) match {
                case Nil => a :+ b
                case (head, b._2) :: tail => a
                case head :: tail => a :+ (head._1, b._2 - head._2)
            }
        })
    }
        
    def sentenceAnagrams(sentence: Sentence): List[Sentence] = {
        def dfs(occurrence: Occurrences): List[Sentence] = occurrence match {
            case Nil => List(List())
            case occurrence => for {
                sub <- combinations(occurrence)
                word <- dictionaryByOccurrences(sub)
                sentence <- dfs(subtract(occurrence, sub))
            } yield word :: sentence
        }
        dfs(sentenceOccurrences(sentence))
    }
}
