use std::cmp::max;
use std::fs::read_to_string;

struct Game {
    index: i32,
    red: i32,
    blue: i32,
    green: i32
}

impl Game {

    fn new() -> Game {
        Game{index: 0, red: 0, blue: 0, green: 0}
    }

    fn parse(line: &str) -> Game {
        let mut game = Game::new();
        let caret = game.parse_game_number(line) + 2; // skip : and ' '

        for grab in line[caret..].split(';') {
            game.parse_grab(grab.trim());
        }

        game
    }

    fn parse_game_number(&mut self, line: &str) -> usize {
        let space = line.find(' ').unwrap() + 1;
        let colon = line.find(':').unwrap();
        self.index = line[space..colon].parse::<i32>().unwrap();
        colon
    }

    fn parse_grab(&mut self, line: &str) {
        for marbles in line.split(", ") {
            self.parse_marbles(marbles);
        }
    }

    fn parse_marbles(&mut self, line: &str) {
        let mut parts = line.split(' ');
        let number = parts.next().unwrap().parse::<i32>().unwrap();
        let color = parts.next().unwrap();

        match color {
            "red" => self.red = max(self.red, number),
            "green" => self.green = max(self.green, number),
            "blue" => self.blue = max(self.blue, number),
            _ => panic!("dafuq")
        };
    }

}

fn main() {
    let mut power = 0;

    for line in read_to_string("input.txt").unwrap().lines() {
        let game = Game::parse(line);
        power += game.red * game.green * game.blue;
    }

    println!("power: {}", power);
}