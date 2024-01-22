pub fn part1() {
    dbg!(include_str!("../../inputs/day-2")
        .trim()
        .split('\n')
        .filter_map(|l| {
            let items = l.split(':').collect::<Vec<&str>>();
            let game_id: u32 = items[0].split(' ').nth(1).unwrap().parse().unwrap();
            let is_valid = items[1].split(|i| i == ',' || i == ';').any(|i| {
                let split: Vec<&str> = i.split(' ').collect();
                let num: u32 = split[1].parse().unwrap();
                match split[2] {
                    "red" if num > 12 => {
                        return true;
                    }
                    "green" if num > 13 => {
                        return true;
                    }
                    "blue" if num > 14 => {
                        return true;
                    }
                    _ => return false,
                }
            });

            if is_valid {
                None
            } else {
                Some(game_id)
            }
        })
        .sum::<u32>());
}

pub fn part2() {
    let content: u32 = include_str!("../../inputs/day-2")
        .trim()
        .split('\n')
        .map(|x| {
            x.split(':')
                .next_back()
                .unwrap()
                .split(|y| y == ',' || y == ';')
                .map(|y| {
                    let mut split = y.trim().split(' ');
                    let num: u32 = split.next().unwrap().parse().unwrap();
                    let color = split.next().unwrap();
                    (num, color)
                })
                .collect::<Vec<(u32, &str)>>()
        })
        .map(|x| {
            x.iter()
                .fold([0, 0, 0], |acc, y| match y.1 {
                    "red" => [acc[0].max(y.0), acc[1], acc[2]],
                    "green" => [acc[0], acc[1].max(y.0), acc[2]],
                    "blue" => [acc[0], acc[1], acc[2].max(y.0)],
                    _ => panic!(),
                })
                .iter()
                .product::<u32>()
        })
        .sum();
    dbg!(content);
}
