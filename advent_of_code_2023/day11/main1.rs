use std::fs::read_to_string;

fn difference(lhs: usize, rhs: usize) -> usize {
    if lhs > rhs {
        return lhs - rhs;
    }
    rhs - lhs
}

fn main() {
    let input = read_to_string("input.txt").unwrap();
    let mut starmap = input.lines().map(|line| {
        let mut vec: Vec<u8> = Vec::new();
        vec.extend_from_slice(line.as_bytes());
        vec
    }).collect::<Vec<_>>();

    let mut index = 0;
    loop {
        if index == starmap.len() {
            break;
        }

        if starmap[index].iter().filter(|ch| { **ch == b'#' }).count() == 0 {
            starmap.insert(index, starmap[index].clone());
            index += 1;
        }

        index += 1;
    }

    index = 0;
    loop {
        if index >= starmap[0].len() {
            break;
        }

        let mut sum = 0;
        for line in &starmap {
            if line[index] == b'#' {
                sum += 1;
            }
        }

        if sum == 0 {
            for line in &mut starmap {    
                line.insert(index, b'.');
            }
            index += 1;
        }

        index += 1;
    }

    let mut stars: Vec<(usize, usize)> = Vec::new();
    for row in 0..starmap.len() {
        for col in 0..starmap[row].len() {
            if starmap[row][col] == b'#' {
                stars.push((row, col));
            }
        }
    }

    let mut sum_difference = 0;
    for start_idx in 0..stars.len() {
        for inner_idx in start_idx..stars.len() {
            sum_difference += difference(stars[start_idx].0, stars[inner_idx].0);
            sum_difference += difference(stars[start_idx].1, stars[inner_idx].1);
        }
    }

    println!("Sum of ranges: {}", sum_difference);
}
