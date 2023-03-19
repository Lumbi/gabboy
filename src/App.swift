//
//  App.swift
//  gabboy
//
//  Created by Gabriel Lumbi on 2023-03-10.
//

import SwiftUI

@main
struct GabboyApp: App {
    var body: some Scene {
        WindowGroup {
            ZStack {
                LCDView()
            }
            .frame(width: 160, height: 144)
            .fixedSize()
        }
    }
}
