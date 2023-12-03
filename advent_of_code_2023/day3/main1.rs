use std::cmp::min;
use std::fs::read_to_string;

fn part_adjacent(schematic: &Vec<Vec<char>>, line: usize, start: usize, end: usize) -> bool {
    let first_line = if line != 0 { line - 1 } else { line };
    let last_line = min(schematic.len() - 1, line + 1);
    let first_char = if start != 0 { start - 1 } else { start };
    let last_char = min(schematic[line].len() - 1, end);

    for line_idx in first_line..=last_line {
        for char_idx in first_char..=last_char {
            if !"0123456789.".contains(schematic[line_idx][char_idx]) {
                return true;
            }
        }
    }

    false
}

fn parse_number(line: &Vec<char>, mut caret: usize) -> (Option<i32>, usize) {
    if !line[caret].is_ascii_digit() {
        return (None, caret + 1);
    }

    let start = caret;
    let end = loop {
        caret += 1;
        if caret == line.len() || !line[caret].is_ascii_digit() {
            break caret;
        }
    };

    (Some(line[start..end].iter().collect::<String>().parse::<i32>().unwrap()), caret)
}

fn main() {
    let schematic: Vec<Vec<char>> = read_to_string("input.txt").unwrap().lines().map(|line| {
        line.chars().collect()
    }).collect();

    let mut sum = 0;

    let mut line = 0;
    while line < schematic.len() {
        let mut caret = 0;

        while caret != schematic[line].len() {
            let (number, next) = parse_number(&schematic[line], caret);
            
            match number {
                Some(_) => (),
                None => {
                    caret = next;
                    continue;
                }
            }

            if part_adjacent(&schematic, line, caret, next) {
                sum += number.unwrap();  
            }

            caret = next;
        }

        line += 1;
        if line == schematic.len() {
            break;
        }
    }
    
    println!("sum: {}", sum);

}