package main

import (
	"bufio"
	"log"
	"os"
	"strconv"
	"strings"
)

type Board struct {
	rows [][]int
}

func (board Board) BoardResult(draw []int) int {
	if len(draw) < 5 {
		return 0
	}
	return board.BoardSum(draw) * draw[len(draw)-1]
}

func (board Board) Win(draw []int) bool {
	for i := 0; i < 5; i++ {
		found := 0
		for j := 0; j < 5; j++ {
			for _, drawElem := range draw {
				if board.rows[i][j] == drawElem {
					found++
				}
			}
		}
		if found == 5 {
			return true
		}
	}
	for i := 0; i < 5; i++ {
		found := 0
		for j := 0; j < 5; j++ {
			for _, drawElem := range draw {
				if board.rows[j][i] == drawElem {
					found++
				}
			}
		}
		if found == 5 {
			return true
		}
	}
	return false
}
func (board Board) BoardSum(draw []int) int {
	result := 0
	for _, row := range board.rows {
		for _, elem := range row {
			found := false
			for _, drawElem := range draw {
				if elem == drawElem {
					found = true
				}
			}
			if !found {
				result += elem
			}
		}
	}

	return result
}

func main() {
	file, err := os.Open("/home/asmirnov/www/fun/advent_of_code_2021/day04/data.txt")
	if err != nil {
		log.Fatal(err)
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	// optionally, resize scanner's capacity for lines over 64K, see next example
	lineN := 0
	var newBoard Board
	boards := make([]Board, 0, 12)
	draw := make([]int, 0, 128)
	for scanner.Scan() {
		line := scanner.Text()
		lineN++
		if lineN == 1 {
			for _, elem := range strings.Split(line, ",") {
				intElem, _ := strconv.Atoi(elem)
				draw = append(draw, intElem)
			}
			continue
		}
		if line == "" {
			if newBoard.rows != nil {
				boards = append(boards, newBoard)
			}
			newBoard = Board{rows: make([][]int, 0, 5)}
			continue
		}
		row := make([]int, 0, 5)
		for _, elem := range strings.Split(line, " ") {
			if elem == " " || elem == "" {
				continue
			}
			intElem, _ := strconv.Atoi(elem)
			row = append(row, intElem)
		}
		newBoard.rows = append(newBoard.rows, row)
		continue
	}
	boards = append(boards, newBoard)
	for i := 5; i <= len(draw); i++ {
		boardLen := len(boards)
		for j := 0; j < boardLen; j++ {
			if boards[j].Win(draw[:i]) {
				if len(boards) == 1 {
					print(boards[j].BoardResult(draw[:i]))
					return
				}
				boards = append(boards[:j], boards[j+1:]...)
				j--
				boardLen--
			}
		}
	}
}
