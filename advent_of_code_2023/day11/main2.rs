use std::fs::read_to_string;

fn walk_row(distance_map: &Vec<(usize, usize)>, start: usize, end: usize) -> usize {
    let mut distance: usize = 0;
    let start_index = if start < end { start } else { end };
    let end_index = if start > end { start } else { end };

    for index in start_index..end_index {
        distance += distance_map[index].0;
    }

    distance
}

fn walk_col(distance_map: &Vec<Vec<(usize, usize)>>, col: usize, start: usize, end: usize) -> usize {
    let mut distance = 0;
    let start_index = if start < end { start } else { end };
    let end_index = if start > end { start } else { end };

    for index in start_index..end_index {
        distance += distance_map[index][col].1;
    }

    distance
}

fn main() {
    let expansion: usize = 1_000_000;
    let input = read_to_string("input.txt").unwrap();
    let starmap = input.lines().map(|line| {
        let mut vec: Vec<u8> = Vec::new();
        vec.extend_from_slice(line.as_bytes());
        vec
    }).collect::<Vec<_>>();

    let mut distance_map = starmap.iter().map(|line| {
        vec![(1 as usize, 1 as usize); line.len()]
    }).collect::<Vec<_>>();

    for index in 0..starmap.len() {
        if starmap[index].iter().filter(|ch| { **ch == b'#' }).count() == 0 {
            for distance in distance_map[index].iter_mut() {
                distance.1 *= expansion;
            }
        }
    }

    let mut index = 0;
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
            for idx in 0..distance_map.len() {
                distance_map[idx][index].0 *= expansion;
            }
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
            sum_difference += walk_col(&distance_map, stars[start_idx].1, stars[start_idx].0, stars[inner_idx].0);
            sum_difference += walk_row(&distance_map[stars[start_idx].0], stars[start_idx].1, stars[inner_idx].1);
        }
    }

    println!("Sum of ranges: {}", sum_difference);
}
