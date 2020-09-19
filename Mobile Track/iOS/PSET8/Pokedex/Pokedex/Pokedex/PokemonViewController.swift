import UIKit

class PokemonViewController: UIViewController {
    var url: String!
    var pokemon_caught: Bool!
    
    @IBOutlet var nameLabel: UILabel!
    @IBOutlet var numberLabel: UILabel!
    @IBOutlet var type1Label: UILabel!
    @IBOutlet var type2Label: UILabel!
    @IBOutlet var catchButton: UIButton!
    @IBOutlet var pokemonImage: UIImageView!
    @IBOutlet var descLabel: UILabel!
    
    @IBAction func toggleCatch() {
        // flip status of pokemon_caught
        if self.pokemon_caught == false {
            self.pokemon_caught = true
            self.catchButton.setTitle("Release Pokemon", for: UIControl.State.normal)
            // Save the status of the pokemon
            UserDefaults.standard.set(true, forKey: self.nameLabel.text!)
        }
        else {
            self.pokemon_caught = false
            self.catchButton.setTitle("Catch Pokemon", for: UIControl.State.normal)
            // Save the status of the pokemon
            UserDefaults.standard.set(false, forKey: self.nameLabel.text!)
        }
    }

    func capitalize(text: String) -> String {
        return text.prefix(1).uppercased() + text.dropFirst()
    }

    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)

        nameLabel.text = ""
        numberLabel.text = ""
        type1Label.text = ""
        type2Label.text = ""
        descLabel.text = ""
        
        
        loadPokemon()
    }

    func loadPokemon() {
        URLSession.shared.dataTask(with: URL(string: url)!) { (data, response, error) in
            guard let data = data else {
                return
            }

            do {
                
                let result = try JSONDecoder().decode(PokemonResult.self, from: data)
                
                // Gets the url of the sprite
                let image_url = URL(string: result.sprites.front_default)!

                // Gets the image data of the sprite
                let image_data = try Data(contentsOf: image_url)
                
                
                
                DispatchQueue.main.async {
                    self.navigationItem.title = self.capitalize(text: result.name)
                    self.nameLabel.text = self.capitalize(text: result.name)
                    self.numberLabel.text = String(format: "#%03d", result.id)
                    // Set the image of pokemon
                    self.pokemonImage.image = UIImage(data: image_data)
                    
                    // Set the pokemon Desc
                    self.getDescLabel(result: result)
//                    //print(self.flavourText!)
//
//                    self.descLabel.text = self.flavourText

                    for typeEntry in result.types {
                        if typeEntry.slot == 1 {
                            self.type1Label.text = typeEntry.type.name
                        }
                        else if typeEntry.slot == 2 {
                            self.type2Label.text = typeEntry.type.name
                        }
                    }
                    
                    // Gets the Saved Status of pokemon. if No status, false is returned
                    self.pokemon_caught = UserDefaults.standard.bool(forKey: self.nameLabel.text!)
                    
                    // Set Text of Button
                    if self.pokemon_caught == false {
                        self.catchButton.setTitle("Catch Pokemon", for: UIControl.State.normal)
                    }
                    else {
                        self.catchButton.setTitle("Release Pokemon", for: UIControl.State.normal)
                    }
                    
                }
                
                
            }
            catch let error {
                print(error)
            }
        }.resume()
    }
    
    func getDescLabel(result: PokemonResult) {
        let pokemon_number = result.id
        let pokemon_desc_string = "https://pokeapi.co/api/v2/pokemon-species/" + String(pokemon_number) + "/"
        
        let pokemon_desc_URL = URL(string: pokemon_desc_string)!
        do {
            let data = try Data(contentsOf: pokemon_desc_URL)
            let result = try JSONDecoder().decode(PokemonSpecies.self, from: data)
            
                let flavourText = result.flavor_text_entries[0].flavor_text
                print(flavourText)
                self.descLabel.text = flavourText.replacingOccurrences(of: "\n", with: " ")
        }
        catch let error {
            print(error)
        }
    }
}
