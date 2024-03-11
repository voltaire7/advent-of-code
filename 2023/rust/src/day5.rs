pub fn part1() {
    let content = include_str!("../../inputs/day-5")
        .trim()
        .split("\n\n")
        // .map(|x| x.split(|y| y == '\n' || y == ' ').collect::<Vec<&str>>())
        .collect::<Vec<&str>>();
    let seeds = content
        .first()
        .unwrap()
        .split_whitespace()
        .skip(1)
        .map(|x| x.parse::<u64>().unwrap())
        .collect::<Vec<u64>>();
    let content = content
        .iter()
        .skip(1)
        .map(|x| {
            let mut x = x
                .split(|y| y == '\n' || y == ' ')
                .skip(2)
                .map(|y| y.parse::<u64>().unwrap());
            (0..x.clone().count() / 3)
                .map(|_| (x.next().unwrap(), x.next().unwrap(), x.next().unwrap()))
                .collect::<Vec<(u64, u64, u64)>>()
        })
        .collect::<Vec<Vec<(u64, u64, u64)>>>();
    let out = seeds
        .into_iter()
        .map(|x| {
            let find_destination = |x, y: &Vec<(u64, u64, u64)>| {
                y.iter()
                    .find_map(|z| {
                        if x >= z.1 && x <= z.1 + z.2 {
                            Some(
                                (0..z.2)
                                    .find_map(|a| if a + z.1 == x { Some(a) } else { None })
                                    .unwrap()
                                    + z.0,
                            )
                        } else {
                            None
                        }
                    })
                    .unwrap_or(x)
            };

            let x = find_destination(x, &content[0]);
            let x = find_destination(x, &content[1]);
            let x = find_destination(x, &content[2]);
            let x = find_destination(x, &content[3]);
            let x = find_destination(x, &content[4]);
            let x = find_destination(x, &content[5]);
            let x = find_destination(x, &content[6]);
            x
        })
        .min();
    dbg!(out);
}

pub fn part2() {
    todo!()
}
