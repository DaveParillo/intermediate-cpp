from docutils import nodes

def setup(app):
    app.add_role('cref', autolink('http://en.cppreference.com/mwiki/index.php?search=%s'))

def autolink(pattern):
    def role(name, rawtext, text, lineno, inliner, options={}, content=[]):
        """Link to a url 

        Returns 2 part tuple containing list of nodes to insert into the
        document and a list of system messages.  Both are allowed to be
        empty.

        :param name: The role name used in the document.
        :param rawtext: The entire markup snippet, with role.
        :param text: The text marked with the role.
        :param lineno: The line number where rawtext appears in the input.
        :param inliner: The inliner instance that called us.
        :param options: Directive options for customization.
        :param content: The directive content for customization.
        """
        if len(text) <= 2:
            msg = inliner.reporter.error(
                'Search string length for cppreference search must be > 2; '
                '"%s" is invalid.' % text, line=lineno)
            prb = inliner.problematic(rawtext, rawtext, msg)
            return [prb], [msg]

        if (':' in text) and ("::" not in text) :
            msg = inliner.reporter.error(
                'Possible namespace error in search string: '
                '"%s". Perhaps you meant "::" ?' % text, line=lineno)
            prb = inliner.problematic(rawtext, rawtext, msg)
            return [prb], [msg]

        url = pattern % (text,)
        node = nodes.reference(rawtext, text, refuri=url, **options)
        return [node], []
    return role


