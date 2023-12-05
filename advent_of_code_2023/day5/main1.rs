use std::{fs::read_to_string, collections::HashMap};

struct Range {
    source: u64,
    destination: u64,
    length: u64
}

impl Range {

    fn parse(line: &str) -> Range {
        let numbers = line.split(' ').map(|num| {
            num.parse::<u64>().unwrap()
        }).collect::<Vec<_>>();

        Range{source: numbers[1], destination: numbers[0], length: numbers[2]}
    }

    fn contains(&self, src: u64) -> bool {
        (self.source..(self.source+self.length)).contains(&src)
    }

    fn map(&self, src: u64) -> u64 {
        self.destination + (src - self.source)
    }

}

struct Mapping {
    from: String,
    to: String,
    ranges: Vec<Range>
}

impl Mapping {

    fn new(from: &str, to: &str) -> Mapping {
        Mapping{from: String::from(from), to: String::from(to), ranges: Vec::new()}
    }

    fn from_direction(line: &str) -> Mapping {
        let parts = line[0..line.find(' ').unwrap()].split('-').collect::<Vec<_>>();
        Mapping::new(parts[0], parts[2])
    }

}

fn parse_seeds(line: &str) -> Vec<u64> {
    line[line.find(' ').unwrap() + 1..line.len()].split(' ').map(|num| {
        num.parse::<u64>().unwrap()
    }).collect::<Vec<_>>()
}

fn map_to_location(mappings: &HashMap<String, Mapping>, from: &String, number: u64) -> u64 {
    if from == "location" {
        return number;
    }

    let mapping: &Mapping = &mappings[from];
    for range in &mapping.ranges {
        if range.contains(number) {
            return map_to_location(mappings, &mapping.to, range.map(number));
        }
    }

    map_to_location(mappings, &mapping.to, number)
}

fn main() {
    let file = read_to_string("input.txt").unwrap();
    let mut lines = file.lines();

    // parse seeds
    let seeds = parse_seeds(lines.next().unwrap());
    lines.next().unwrap(); // skip empty line below seeds

    let mut mappings: HashMap<String, Mapping> = HashMap::new();

    loop {
        let line = match lines.next() {
            Some(line) => line,
            None => break
        };

        let mut mapping = Mapping::from_direction(line);

        // now we parse ranges
        loop {
            let line = match lines.next() {
                Some(line) => line,
                None => break
            };

            if line.is_empty() {
                break
            }

            mapping.ranges.push(Range::parse(line));
        }

        mapping.ranges.sort_by(|a, b| a.source.cmp(&b.source));
        mappings.insert(mapping.from.clone(), mapping);
    }

    let min_location = seeds.iter().map(|seed| {
        map_to_location(&mappings, &String::from("seed"), *seed)
    }).min().unwrap();

    println!("min location: {}", min_location);   
}