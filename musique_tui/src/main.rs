use ratatui::{prelude::*, widgets::*};
use crossterm::event::{self, Event, KeyCode};
use std::fs::OpenOptions;
use std::io::Write;

const PIPE: &str = "/tmp/musique_cmd";

fn send(cmd: &str) {
    if let Ok(mut f) = OpenOptions::new().write(true).open(PIPE) {
        let _ = writeln!(f, "{}", cmd);
    }
}

fn main() -> std::io::Result<()> {
    crossterm::terminal::enable_raw_mode()?;

    let mut terminal = ratatui::init();

    loop {
        terminal.draw(|f| {
            let area = f.size();
            let block = Block::default()
                .title("Musique Controller")
                .borders(Borders::ALL);

            let text = Paragraph::new(
                "SPACE play/pause\nM mute\n↑ ↓ volume\n← → seek\nQ quit",
            );

            f.render_widget(block, area);
            f.render_widget(text, area);
        })?;

        if event::poll(std::time::Duration::from_millis(50))? {
            if let Event::Key(k) = event::read()? {
                match k.code {
                    KeyCode::Char('q') => break,

                    KeyCode::Char(' ') => send("space"),
                    KeyCode::Char('m') => send("mute"),

                    KeyCode::Up => send("up"),
                    KeyCode::Down => send("down"),
                    KeyCode::Left => send("left"),
                    KeyCode::Right => send("right"),

                    _ => {}
                }
            }
        }
    }

    ratatui::restore();
    crossterm::terminal::disable_raw_mode()?;
    Ok(())
}