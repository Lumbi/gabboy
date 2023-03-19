//
//  LCDViewController.swift
//  gabboy
//
//  Created by Gabriel Lumbi on 2023-03-17.
//

import Foundation
import Cocoa
import SwiftUI

class LCDViewController: NSViewController {
    private let bridge = Bridge()
    private var lcdTimer: Timer?
    private var screen: Screen?

    override func loadView() {
        self.view = NSView()

        let screen = Screen(bridge: bridge)
        view.addSubview(screen)
        screen.translatesAutoresizingMaskIntoConstraints = false
        screen.topAnchor.constraint(equalTo: view.topAnchor).isActive = true
        screen.bottomAnchor.constraint(equalTo: view.bottomAnchor).isActive = true
        screen.leadingAnchor.constraint(equalTo: view.leadingAnchor).isActive = true
        screen.trailingAnchor.constraint(equalTo: view.trailingAnchor).isActive = true
        self.screen = screen

        bridge.load()

        lcdTimer = Timer.scheduledTimer(withTimeInterval: 1.0 / 30.0, repeats: true) { [weak self] _ in
            self?.screen?.redraw()
        }

        // Dangerous multi-threading!
        // Not the end of the world but the LCD data is written in a background thread and read from the main thread
        // so there's the main thread could be reading LCD data while the emulator is writing to it.
        // TODO: Refactor LCD to update LCD data during VBlank
        DispatchQueue.global(qos: .userInteractive).async { [weak self] in
            while (true) {
                self?.bridge.frame()
                Thread.sleep(forTimeInterval: 1.0 / 60.0)
            }
        }

        lcdTimer?.fire()
    }

    class Screen: NSView {
        private let bridge: Bridge
        private let lightest = NSColor(red: 155.0 / 255.0, green: 188.0 / 255.0, blue: 15.0 / 255.0, alpha: 1)
        private let darkest = NSColor(red: 15.0 / 255.0, green: 56.0 / 255.0, blue: 15.0 / 255.0, alpha: 1)

        init(bridge: Bridge) {
            self.bridge = bridge
            super.init(frame: .zero)
        }

        required init?(coder: NSCoder) {
            fatalError("init(coder:) has not been implemented")
        }

        func redraw() {
            setNeedsDisplay(bounds)
        }

        override func draw(_ dirtyRect: NSRect) {
            let lcd = bridge.lcd()!

            lightest.setFill()
            bounds.fill()

            for index in 0..<23040 {
                let x = index % 160
                let y = index / 160
                if (lcd + x + y * 256).pointee > 0 {
                    darkest.setFill()
                    NSRect(
                        origin: .init(x: CGFloat(x), y: CGFloat(144 - y)), // Cocoa origin is bottom-left
                        size: .init(width: 1, height: 1)
                    )
                    .fill()
                }
            }
        }
    }
}


struct LCDView: NSViewControllerRepresentable {
    func makeNSViewController(context: Self.Context) -> LCDViewController { LCDViewController() }
    func updateNSViewController(_ nsViewController: LCDViewController, context: Self.Context) {}
}
