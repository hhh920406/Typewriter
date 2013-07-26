package streams

import common._

trait Solver extends GameDef {

    def done(b: Block): Boolean = b == Block(goal, goal)
  
    def neighborsWithHistory(b: Block, history: List[Move]): Stream[(Block, List[Move])] = {
        b.legalNeighbors.map(x => (x._1, x._2 :: history)).toStream
    }

    def newNeighborsOnly(neighbors: Stream[(Block, List[Move])],
                         explored: Set[Block]): Stream[(Block, List[Move])] = {
        neighbors.filterNot(x => explored.contains(x._1))
    }

    def from(initial: Stream[(Block, List[Move])],
             explored: Set[Block]): Stream[(Block, List[Move])] = {
        val neighbors = newNeighborsOnly(neighborsWithHistory(initial.head._1, initial.head._2), explored)
        if (neighbors.isEmpty && initial.tail.isEmpty) initial
        else initial.head #:: from(initial.tail ++ neighbors, explored ++ neighbors.map(x => x._1))
    }

    lazy val pathsFromStart: Stream[(Block, List[Move])] = from(Stream((startBlock, List())), Set(startBlock))
    lazy val pathsToGoal: Stream[(Block, List[Move])] = pathsFromStart.filter(x => done(x._1))
    lazy val solution: List[Move] = if (pathsToGoal.isEmpty) List() else pathsToGoal.minBy(_._2.size)._2
}
