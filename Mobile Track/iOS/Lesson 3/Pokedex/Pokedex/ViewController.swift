//
//  ViewController.swift
//  Pokedex
//
//  Created by Clement Koh Sze Hong on 15/9/20.
//  Copyright © 2020 Clement Koh Sze Hong. All rights reserved.
//

import UIKit

class ViewController: UITableViewController {
    
    var pokemon: [Pokemon] = []
    
    func capitalise(text: String) -> String {
        return text.prefix(1).uppercased() + text.dropFirst()
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Save url into a variable
        let url = URL(string: "https://pokeapi.co/api/v2/pokemon?limit=151")
        guard let u = url else {
            return
        }
        URLSession.shared.dataTask(with: u) { (data, response, error) in
            // Ensure that data is not optional
            guard let data = data else {
                return
            }
            
            // Decode JSON
            // PokemonList.self is referencing to Type to decode into .self is to reference to the struct
            do {
                let pokemonList = try JSONDecoder().decode(PokemonList.self, from: data)
                self.pokemon = pokemonList.results
                
                DispatchQueue.main.async {
                    self.tableView.reloadData()
                }
            }
            catch let error {
                print("\(error)")
            }
        }.resume()
    }
    
    
    
    // How many section does this view have
    override func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }

    // How many rows does this section have
    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return pokemon.count
    }
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        // What to do with each cell we want to display
        let cell = tableView.dequeueReusableCell(withIdentifier: "PokemonCell", for: indexPath)
        cell.textLabel?.text = capitalise(text: pokemon[indexPath.row].name)
        return cell
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "PokemonSegue" {
            if let destination = segue.destination as? PokemonViewController {
                destination.pokemon = pokemon[tableView.indexPathForSelectedRow!.row]
            }
        }
    }
}

