use core::panic;
use std::{fs::read_to_string, ops};

#[derive(Clone, Copy, PartialEq, Eq, Debug)]
struct Point {
    x: isize,
    y: isize
}

impl Point {
    fn new(x: isize, y: isize) -> Point {
        Point {x, y}
    }

    fn moved(&self, dx: isize, dy: isize) -> Point {
        return Point::new(self.x + dx, self.y + dy);
    }

    fn moves(&self, instruction: u8) -> (Point, Point) {
        match instruction {
            b'|' => (self.moved(0, 1), self.moved(0, -1)),
            b'-' => (self.moved(1, 0), self.moved(-1, 0)),
            b'L' => (self.moved(0, -1), self.moved(1, 0)),
            b'J' => (self.moved(-1, 0), self.moved(0, -1)),
            b'7' => (self.moved(-1, 0), self.moved(0, 1)),
            b'F' => (self.moved(1, 0), self.moved(0, 1)),
            _ => (self.clone(), self.clone())
        }
    }

    fn get_instruction(&self, map: &Vec<&[u8]>) -> Option<u8> {
        let x = self.x as usize;
        let y = self.y as usize;
        
        if self.y < 0 || y >= map.len() {
            return None;
        }

        if self.x < 0 || x >= map[y].len() {
            return None;
        }

        Some(map[y][x])
    }
}

impl ops::Add for &Point {
    type Output = Point;

    fn add(self, rhs: &Point) -> Point {
        Point::new(self.x + rhs.x, self.y + rhs.y)
    }
}

impl ops::Add<&(isize, isize)> for &Point {
    type Output = Point;

    fn add(self, rhs: &(isize, isize)) -> Point {
        Point::new(self.x + rhs.0, self.y + rhs.1)
    }
}

fn find_start(map: &Vec<&[u8]>) -> Point {
    for ypos in 0..map.len() {
        for xpos in 0..map[ypos].len() {
            if map[ypos][xpos] == b'S' {
                return Point::new(xpos as isize, ypos as isize);
            }
        }
    }

    Point::new(0, 0)
}

fn is_connected(instruction: &Option<u8>, start: &Point, end: &Point) -> bool {
    match instruction {
        None => false,
        Some(instr) => {
            let (p1, p2) = start.moves(*instr);
            p1 == *end || p2 == *end 
        }
    }
}

fn find_connections(map: &Vec<&[u8]>, position: &Point) -> (Point, Point) {
    let mut moves: Vec<Point> = Vec::new();

    if is_connected(&position.moved(-1, 0).get_instruction(map), &position.moved(-1, 0), position) {
        moves.push(position.moved(-1, 0));
    }
    if is_connected(&position.moved(1, 0).get_instruction(map), &position.moved(1, 0), position) {
        moves.push(position.moved(1, 0));
    }
    if is_connected(&position.moved(0, -1).get_instruction(map), &position.moved(0, -1), position) {
        moves.push(position.moved(1, 0));
    }
    if is_connected(&position.moved(0, 1).get_instruction(map), &position.moved(0, 1), position) {
        moves.push(position.moved(0, 1));
    }

    if moves.len() != 2 {
        panic!("Got more then two moves :(");
    }

    (moves[0], moves[1])
}

fn write(map: &mut Vec<Vec<i32>>, pos: &Point, val: i32) {
    map[pos.y as usize][pos.x as usize] = val;
}

fn has_been_walked(map: &Vec<Vec<i32>>, pos: &Point) -> bool {
    map[pos.y as usize][pos.x as usize] != -1
}

fn step(map: &Vec<&[u8]>, distances: &mut Vec<Vec<i32>>, pos: &Point, step: i32) -> Point {
    let (p1, p2) = pos.moves(pos.get_instruction(map).unwrap());

    if !has_been_walked(&distances, &p1) {
        write(distances, &p1, step);
        return p1;
    }

    if !has_been_walked(&distances, &p2) {
        write(distances, &p2, step);
        return p2;
    }
    
    // jup jup
    panic!("Result is step {}", step);
}

fn print_distance_map(map: &Vec<Vec<i32>>) {
    for y in 0..map.len() {
        for x in 0..map[y].len() {
            if map[y][x] == -1 {
                print!(". ");
            } else {
                print!("{:1} ", map[y][x]);
            }
        }
        println!();
    }
}

fn main() {
    let input = read_to_string("input.txt").unwrap();
    let map = input.lines().map(|line| { line.as_bytes() }).collect::<Vec<_>>();
    let mut distance_map: Vec<Vec<i32>> = vec![vec![-1; map[0].len()]; map.len()];

    let start = find_start(&map);
    write(&mut distance_map, &start, 0);

    let mut steps = 2;
    let (mut p1, mut p2) = find_connections(&map, &start);
    write(&mut distance_map, &p1, 1);
    write(&mut distance_map, &p2, 1);

    loop {
        p1 = step(&map, &mut distance_map, &p1, steps);
        p2 = step(&map, &mut distance_map, &p2, steps);
        steps += 1;
    }

}