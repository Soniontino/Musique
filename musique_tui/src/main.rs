use ratatui::{prelude::*, widgets::*};
use crossterm::event::{self, eventi KeyCode};
use std::fs::OpenOptions;
use std::io::Write;

const PİPE: &str = "/tmp"