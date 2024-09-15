#![allow(dead_code, unused_parens, unused_variables, unused_mut)]

use std::{thread::sleep, time::Duration};

fn which_to_take(step_global:usize, step_local:usize) -> usize {
    if (step_local<step_global) { step_local }
    else { 1+step_local }
}

fn reduce_to_2(mut matrix:Vec<Vec<Vec<i32>>>, init_size:usize) -> i32 {
    loop {

        let q = matrix.clone();
        let mut podhodyashiy_index:usize = &q.len()-1;
        let mut elem = &q[podhodyashiy_index];

        while elem.len()==2 {
            podhodyashiy_index-=1;
            elem = &q[podhodyashiy_index];
        }
        for i in 0..elem.len() {
            let mut new_thing:Vec<Vec<i32>> = vec![Vec::new();elem.len()-1];
            for x in 0..elem.len()-1 {
                for y in 0..elem.len()-1 {
                    new_thing[x].push( q[podhodyashiy_index][1+x]
                                        [which_to_take(i, y)] );
                    if x==0 {new_thing[x][y] *= ((-1 as i32).pow(i as u32))*(q[podhodyashiy_index][0][i]);}
                }
            }
            matrix.push(new_thing);
        }
        matrix.remove(podhodyashiy_index);
        //println!("{matrix:?}\n");

        if matrix.iter().all(|elem| elem.len()==2) { break; }
    }

    let mut qq = Vec::new();
    //println!("\n\n{:?}", matrix);
    for e in matrix {
        //println!("{}",e[0][0]*e[1][1]-e[0][1]*e[1][0]);
        qq.push(e[0][0]*e[1][1] - e[0][1]*e[1][0]);
    }
    return qq.iter().sum();
}

fn main() {
    let size:usize = 5;
    let mut matrix:Vec<Vec<Vec<i32>>> = vec![vec![
        vec![4, 3, 20,50,41], 
        vec![5, 21,22,34,47], 
        vec![11,13,49,33,35],
        vec![44,7, 2, 1, 9 ], 
        vec![17,18,31,29,39]
    ]];
    //println!("{:?}\n",matrix);
    let q = reduce_to_2(matrix, size);
    println!("\n\n{:?}", q);
}
