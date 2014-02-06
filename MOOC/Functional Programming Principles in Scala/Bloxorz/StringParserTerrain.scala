package streams

import common._

trait StringParserTerrain extends GameDef {
    val level: String
    
    def terrainFunction(levelVector: Vector[Vector[Char]]): Pos => Boolean = {
        (pos: Pos) => pos.x >= 0 && pos.x < levelVector.length && pos.y >= 0 && pos.y < levelVector(pos.x).length && levelVector(pos.x)(pos.y) != '-'
    }
    
    def findChar(c: Char, levelVector: Vector[Vector[Char]]): Pos = {
        lazy val x = levelVector.indexWhere(_.contains(c))
        Pos(x, levelVector(x).indexOf(c))
    }
    private lazy val vector: Vector[Vector[Char]] = Vector(level.split("\n").map(str => Vector(str: _*)): _*)
    lazy val terrain: Terrain = terrainFunction(vector)
    lazy val startPos: Pos = findChar('S', vector)
    lazy val goal: Pos = findChar('T', vector)
}
