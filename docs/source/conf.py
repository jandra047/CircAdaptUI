project = "CircAdaptUI"
copyright = "2024, Andrija Plavetić"
author = "Andrija Plavetić"

extensions = [
    "breathe"
]

# Breathe Configuration
breathe_domain_by_extension = {
    "h": "cpp",
}

html_static_path = ['_static']

html_theme = "sphinx_rtd_theme"
default_dark_mode = True

def setup(app):
    app.add_css_file('styles.css')
