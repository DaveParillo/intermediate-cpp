from docutils import nodes

def setup(app):
    app.add_role('cppref', autolink('http://en.cppreference.com/mwiki/index.php?search=%s'))

def autolink(pattern):
    def role(name, rawtext, text, lineno, inliner, options={}, content=[]):
        url = pattern % (text,)
        node = nodes.reference(rawtext, text, refuri=url, **options)
        return [node], []
    return role
