# Installation Instructions:
# 1. Install the translation library:
#    pip install googletrans==4.0.0-rc1
#
# 2. IMPORTANT FOR PYTHON 3.13 or 3.14+ USERS:
#    If you get a "ModuleNotFoundError: No module named 'cgi'" error,
#    run the following command to restore backward compatibility:
#    pip install legacy-cgi

from googletrans import Translator, LANGUAGES

def translate_text():
    """
    A simple function to translate text from one language to another.
    """
    # Create an instance of the Translator
    translator = Translator()

    print("--- Simple Language Converter ---")

    # 1. Get the text to translate from the user
    try:
        text_to_translate = input("Enter the text you want to translate: ")
        if not text_to_translate:
            print("You didn't enter any text. Exiting.")
            return

        # 2. Get the source language
        print("\nCommon Language Codes: en (English), es (Spanish), fr (French), de (German), ja (Japanese), ko (Korean), zh-cn (Chinese Simplified)")
        print("You can also just press ENTER to let the app auto-detect the language.")
        src_lang = input("Enter the source language code (e.g., 'en'): ").lower()

        # 3. Get the target language
        dest_lang = input("Enter the target language code (e.g., 'es'): ").lower()
        
        # Check if the target language code is valid
        if dest_lang not in LANGUAGES and dest_lang not in LANGUAGES.values():
            print(f"Error: '{dest_lang}' is not a valid language code.")
            print("Please use codes like 'en', 'es', 'fr', etc.")
            return

        # 4. Perform the translation
        print(f"\nTranslating '{text_to_translate}'...")
        
        # Use auto-detection if no source language is provided
        if not src_lang:
            translation = translator.translate(text_to_translate, dest=dest_lang)
            detected_lang_code = translation.src
            detected_lang_name = LANGUAGES.get(detected_lang_code, "Unknown")
            print(f"Auto-detected source language: {detected_lang_name} ({detected_lang_code})")
        else:
            # Use the specified source language
            if src_lang not in LANGUAGES and src_lang not in LANGUAGES.values():
                 print(f"Warning: '{src_lang}' is not a recognized language code, but we will try anyway.")
            translation = translator.translate(text_to_translate, src=src_lang, dest=dest_lang)

        # 5. Print the result
        print("-" * 30)
        print(f"Translation: {translation.text}")
        print("-" * 30)

    except Exception as e:
        print(f"\nAn error occurred. This can happen for a few reasons:")
        print("1. You might not have an internet connection.")
        print("2. The 'googletrans' library might not be installed correctly.")
        print(f"   (Try running: pip install googletrans==4.0.0-rc1)")
        print("3. If you are on Python 3.13+, you need the compatibility pack:")
        print("   (Try running: pip install legacy-cgi)")
        print(f"Error details: {e}")

# Run the function when the script is executed
if __name__ == "__main__":
    translate_text()


# run it from your terminal with:
# python Language_Translator.py