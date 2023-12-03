use std::cmp::min;
use std::collections::HashMap;
use std::fs::read_to_string;

fn register_gears(schematic: &Vec<Vec<char>>, gear_mapping: &mut HashMap<(usize, usize), Vec<usize>>, number: usize, line: usize, start: usize, end: usize) {
    let first_line = if line != 0 { line - 1 } else { line };
    let last_line = min(schematic.len() - 1, line + 1);
    let first_char = if start != 0 { start - 1 } else { start };
    let last_char = min(schematic[line].len() - 1, end);
    
    for line_idx in first_line..=last_line {
        for char_idx in first_char..=last_char {
            if schematic[line_idx][char_idx] == '*' {
                gear_mapping.entry((line_idx, char_idx)).or_insert(Vec::new()).push(number);
            }
        }
    }
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

    let mut gear_mapping: HashMap<(usize, usize), Vec<usize>> = HashMap::new();

    let mut line = 0;
    while line < schematic.len() {
        let mut caret = 0;

        while caret < schematic[line].len() {
            let (number, next) = parse_number(&schematic[line], caret);

            match number {
                Some(_) => (),
                None => {
                    caret = next;
                    continue;
                }
            }

            register_gears(&schematic, &mut gear_mapping, number.unwrap() as usize, line, caret, next);
            caret = next;
        }

        line += 1;
    }

    let mut sum = 0;
    for gear in gear_mapping.values() {
        if gear.len() == 2 {
            sum += gear[0] * gear[1];
        }
    }

    println!("sum: {}", sum);
}