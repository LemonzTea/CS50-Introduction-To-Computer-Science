//
//  ViewController.swift
//  Fiftygram
//
//  Created by Clement Koh Sze Hong on 21/9/20.
//  Copyright © 2020 Clement Koh Sze Hong. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UIImagePickerControllerDelegate, UINavigationControllerDelegate {
    @IBOutlet var imageView: UIImageView!
    let context = CIContext()
    var original: UIImage?
    
    
    @IBAction func ChoosePhoto() {
        // Check if permission is allowed
        if UIImagePickerController.isSourceTypeAvailable(.photoLibrary) {
            let picker = UIImagePickerController()
            // Set properties of picker
            // Set how to respond to user selecting an image
            picker.delegate = self
            
            // Set the source of the photo
            picker.sourceType = .photoLibrary
            navigationController?.present(picker, animated: true, completion: nil)
        }
    }
    
    // Reger to documentation
    @IBAction func ApplySephia() {
        // Ensure that original image is not nil
        if self.original == nil {
            return
        }
        
        //Create object
        let filter = CIFilter(name: "CISepiaTone")
        filter?.setValue(0.5, forKey: kCIInputIntensityKey)
        display(filter: filter!)

    }

    @IBAction func ApplyNoir() {
        // Ensure that original image is not nil
        if self.original == nil {
            return
        }
        
        //Create object
        let filter = CIFilter(name: "CIPhotoEffectNoir")
        display(filter: filter!)

    }
    
    @IBAction func ApplyVintage() {
        // Ensure that original image is not nil
        if self.original == nil {
            return
        }
        
        //Create object
        let filter = CIFilter(name: "CIPhotoEffectProcess")
        display(filter: filter!)

    }
    
    func display(filter: CIFilter) {
        filter.setValue(CIImage(image: self.original!), forKey: kCIInputImageKey)
        let output = filter.outputImage
        imageView.image = UIImage(cgImage: self.context.createCGImage(output!, from: output!.extent)!)
    }
    
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey : Any]) {
        
        // Close image picker
        navigationController?.dismiss(animated: true, completion: nil)
        if let image = info[UIImagePickerController.InfoKey.originalImage] as? UIImage {
            imageView.image = image
            self.original = image
        }
    }
    
}

