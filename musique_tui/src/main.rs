use ratatui::{prelude::*, widgets::*};
use crossterm::event::{self, eventi KeyCode};
use std::fs::OpenOptions;
use std::io::Write;

const PİPE: &str = "/tmp/musique_cmd"

fn send(cmd: &str ) {
    if let ok(mut f) = OpenOptions::new().write(true).open(PİPE) {
        let _ = writeln!(f, "{}", cmd);

    }
}

fn main